/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*               This file is part of the program and library                */
/*    PaPILO --- Parallel Presolve for Integer and Linear Optimization       */
/*                                                                           */
/* Copyright (C) 2020  Konrad-Zuse-Zentrum                                   */
/*                     fuer Informationstechnik Berlin                       */
/*                                                                           */
/* This program is free software: you can redistribute it and/or modify      */
/* it under the terms of the GNU Lesser General Public License as published  */
/* by the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU Lesser General Public License for more details.                       */
/*                                                                           */
/* You should have received a copy of the GNU Lesser General Public License  */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>.    */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _PAPILO_IO_MPS_PARSER_HPP_
#define _PAPILO_IO_MPS_PARSER_HPP_

#include "papilo/core/ConstraintMatrix.hpp"
#include "papilo/core/Objective.hpp"
#include "papilo/core/Problem.hpp"
#include "papilo/core/VariableDomains.hpp"
#include "papilo/misc/Flags.hpp"
#include "papilo/misc/Hash.hpp"
#include "papilo/misc/Num.hpp"
#include "pdqsort/pdqsort.h"
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/utility/string_ref.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <tuple>
#include <utility>

namespace papilo
{

template <typename REAL, bool isfptype = num_traits<REAL>::is_floating_point>
struct RealParseType
{
   using type = double;
};

template <typename REAL>
struct RealParseType<REAL, true>
{
   using type = REAL;
};

/// Parser for mps files in fixed and free format
template <typename REAL>
class MpsParser
{
   static_assert(
       num_traits<typename RealParseType<REAL>::type>::is_floating_point,
       "the parse type must be a floating point type" );

 public:
   static Problem<REAL>
   loadProblem( const std::string& filename )
   {
      MpsParser<REAL> parser;

      Problem<REAL> problem;

      if( !parser.parseFile( filename ) )
         return problem;

      assert( parser.nnz >= 0 );

      Vec<REAL> obj_vec( size_t( parser.nCols ), REAL{0.0} );

      for( auto i : parser.coeffobj )
         obj_vec[i.first] = i.second;

      problem.setObjective( std::move( obj_vec ), parser.objoffset );
      problem.setConstraintMatrix(
          SparseStorage<REAL>{std::move( parser.entries ), parser.nCols,
                              parser.nRows, true},
          std::move( parser.rowlhs ), std::move( parser.rowrhs ),
          std::move( parser.row_flags ), true );
      problem.setVariableDomains( std::move( parser.lb4cols ),
                                  std::move( parser.ub4cols ),
                                  std::move( parser.col_flags ) );
      problem.setVariableNames( std::move( parser.colnames ) );
      problem.setName( std::move( filename ) );
      problem.setConstraintNames( std::move( parser.rownames ) );

      problem.setInputTolerance(
          REAL{pow( typename RealParseType<REAL>::type{10},
                    -std::numeric_limits<
                        typename RealParseType<REAL>::type>::digits10 )} );
      return problem;
   }

 private:
   MpsParser() {}

   /// load LP from MPS file as transposed triplet matrix
   bool
   parseFile( const std::string& filename );

   void
   parse( boost::iostreams::filtering_istream& file );

   enum class boundtype
   {
      LE,
      EQ,
      GE
   };

   enum class parsekey
   {
      ROWS,
      COLS,
      RHS,
      RANGES,
      BOUNDS,
      NONE,
      END,
      FAIL,
      COMMENT
   };

   void
   printErrorMessage( parsekey keyword )
   {
      switch( keyword )
      {
      case parsekey::ROWS:
         std::cerr << "read error in section ROWS " << std::endl;
         break;
      case parsekey::COLS:
         std::cerr << "read error in section COLUMNS " << std::endl;
         break;
      case parsekey::RHS:
         std::cerr << "read error in section RHS " << std::endl;
         break;
      case parsekey::BOUNDS:
         std::cerr << "read error in section BOUNDS " << std::endl;
         break;
      case parsekey::RANGES:
         std::cerr << "read error in section RANGES " << std::endl;
         break;
      default:
         std::cerr << "undefined read error " << std::endl;
         break;
      }
   };

   /*
    * data for mps problem
    */

   Vec<Triplet<REAL>> entries;
   Vec<std::pair<int, REAL>> coeffobj;
   Vec<REAL> rowlhs;
   Vec<REAL> rowrhs;
   Vec<std::string> rownames;
   Vec<std::string> colnames;

   HashMap<std::string, int> rowname2idx;
   HashMap<std::string, int> colname2idx;
   Vec<REAL> lb4cols;
   Vec<REAL> ub4cols;
   Vec<boundtype> row_type;
   Vec<RowFlags> row_flags;
   Vec<ColFlags> col_flags;
   REAL objoffset = 0;

   int nCols = 0;
   int nRows = 0;
   int nnz = -1;

   /// checks first word of strline and wraps it by it_begin and it_end
   parsekey
   checkFirstWord( std::string& strline, std::string::iterator& it,
                   boost::string_ref& word_ref ) const;

   parsekey
   parseDefault( boost::iostreams::filtering_istream& file ) const;

   parsekey
   parseRows( boost::iostreams::filtering_istream& file,
              Vec<boundtype>& rowtype );

   parsekey
   parseCols( boost::iostreams::filtering_istream& file,
              const Vec<boundtype>& rowtype );

   parsekey
   parseRhs( boost::iostreams::filtering_istream& file );

   parsekey
   parseRanges( boost::iostreams::filtering_istream& file );

   parsekey
   parseBounds( boost::iostreams::filtering_istream& file );
};

template <typename REAL>
typename MpsParser<REAL>::parsekey
MpsParser<REAL>::checkFirstWord( std::string& strline,
                                 std::string::iterator& it,
                                 boost::string_ref& word_ref ) const
{
   using namespace boost::spirit;

   it = strline.begin() + strline.find_first_not_of( " " );
   std::string::iterator it_start = it;

   qi::parse( it, strline.end(), qi::lexeme[+qi::graph] ); // todo

   const std::size_t length = std::distance( it_start, it );

   boost::string_ref word( &( *it_start ), length );

   word_ref = word;

   if( word.front() == 'R' ) // todo
   {
      if( word == "ROWS" )
         return MpsParser<REAL>::parsekey::ROWS;
      else if( word == "RHS" )
         return MpsParser<REAL>::parsekey::RHS;
      else if( word == "RANGES" )
         return MpsParser<REAL>::parsekey::RANGES;
      else
         return MpsParser<REAL>::parsekey::NONE;
   }
   else if( word == "COLUMNS" )
      return MpsParser<REAL>::parsekey::COLS;
   else if( word == "BOUNDS" )
      return MpsParser<REAL>::parsekey::BOUNDS;
   else if( word == "ENDATA" )
      return MpsParser<REAL>::parsekey::END;
   else
      return MpsParser<REAL>::parsekey::NONE;
}

template <typename REAL>
typename MpsParser<REAL>::parsekey
MpsParser<REAL>::parseDefault( boost::iostreams::filtering_istream& file ) const
{
   std::string strline;
   getline( file, strline );

   std::string::iterator it;
   boost::string_ref word_ref;
   return checkFirstWord( strline, it, word_ref );
}

template <typename REAL>
typename MpsParser<REAL>::parsekey
MpsParser<REAL>::parseRows( boost::iostreams::filtering_istream& file,
                            Vec<boundtype>& rowtype )
{
   using namespace boost::spirit;

   std::string strline;
   size_t nrows = 0;
   bool hasobj = false;

   while( getline( file, strline ) )
   {
      bool isobj = false;
      std::string::iterator it;
      boost::string_ref word_ref;
      MpsParser<REAL>::parsekey key = checkFirstWord( strline, it, word_ref );

      // start of new section?
      if( key != parsekey::NONE )
      {
         nRows = int( nrows );
         if( !hasobj )
         {
            std::cout << "WARNING: no objective row found" << std::endl;
            rowname2idx.emplace( "artificial_empty_objective", -1 );
         }

         return key;
      }

      if( word_ref.front() == 'G' )
      {
         rowlhs.push_back( REAL{0.0} );
         rowrhs.push_back( REAL{0.0} );
         row_flags.emplace_back( RowFlag::RHS_INF );
         rowtype.push_back( boundtype::GE );
      }
      else if( word_ref.front() == 'E' )
      {
         rowlhs.push_back( REAL{0.0} );
         rowrhs.push_back( REAL{0.0} );
         row_flags.emplace_back( RowFlag::EQUALITY );
         rowtype.push_back( boundtype::EQ );
      }
      else if( word_ref.front() == 'L' )
      {
         rowlhs.push_back( REAL{0.0} );
         rowrhs.push_back( REAL{0.0} );
         row_flags.emplace_back( RowFlag::LHS_INF );
         rowtype.push_back( boundtype::LE );
      }
      else if( word_ref.front() ==
               'N' ) // todo properly treat multiple free rows
      {
         if( hasobj )
         {
            rowlhs.push_back( REAL{0.0} );
            rowrhs.push_back( REAL{0.0} );
            RowFlags rowf;
            rowf.set( RowFlag::LHS_INF, RowFlag::RHS_INF );
            row_flags.emplace_back( rowf );
            rowtype.push_back( boundtype::LE );
         }
         else
         {
            isobj = true;
            hasobj = true;
         }
      }
      else if( word_ref.empty() ) // empty line
         continue;
      else
         return parsekey::FAIL;

      std::string rowname = ""; // todo use ref

      // get row name
      qi::phrase_parse( it, strline.end(), qi::lexeme[+qi::graph], ascii::space,
                        rowname ); // todo use ref

      // todo whitespace in name possible?
      auto ret = rowname2idx.emplace( rowname, isobj ? ( -1 ) : ( nrows++ ) );

      if( !isobj )
         rownames.push_back( rowname );

      if( !ret.second )
      {
         std::cerr << "duplicate row " << rowname << std::endl;
         return parsekey::FAIL;
      }
   }

   return parsekey::FAIL;
}

template <typename REAL>
typename MpsParser<REAL>::parsekey
MpsParser<REAL>::parseCols( boost::iostreams::filtering_istream& file,
                            const Vec<boundtype>& rowtype )
{
   using namespace boost::spirit;

   std::string colname = "";
   std::string strline;
   int rowidx;
   int ncols = 0;
   int colstart = 0;
   bool integral_cols = false;

   auto parsename = [&rowidx, this]( std::string name ) {
      auto mit = rowname2idx.find( name );

      assert( mit != rowname2idx.end() );
      rowidx = mit->second;

      if( rowidx >= 0 )
         this->nnz++;
      else
         assert( -1 == rowidx );
   };

   auto addtuple = [&rowidx, &ncols,
                    this]( typename RealParseType<REAL>::type coeff ) {
      if( rowidx >= 0 )
         entries.push_back( std::make_tuple( ncols - 1, rowidx, REAL{coeff} ) );
      else
         coeffobj.push_back( std::make_pair( ncols - 1, REAL{coeff} ) );
   };

   while( getline( file, strline ) )
   {
      std::string::iterator it;
      boost::string_ref word_ref;
      MpsParser<REAL>::parsekey key = checkFirstWord( strline, it, word_ref );

      // start of new section?
      if( key != parsekey::NONE )
      {
         if( ncols > 1 )
            pdqsort( entries.begin() + colstart, entries.end(),
                     []( Triplet<REAL> a, Triplet<REAL> b ) {
                        return std::get<1>( b ) > std::get<1>( a );
                     } );

         return key;
      }

      // check for integrality marker
      std::string marker = ""; // todo use ref
      std::string::iterator it2 = it;

      qi::phrase_parse( it2, strline.end(), qi::lexeme[+qi::graph],
                        ascii::space, marker );

      if( marker == "'MARKER'" )
      {
         marker = "";
         qi::phrase_parse( it2, strline.end(), qi::lexeme[+qi::graph],
                           ascii::space, marker );

         if( ( integral_cols && marker != "'INTEND'" ) ||
             ( !integral_cols && marker != "'INTORG'" ) )
         {
            std::cerr << "integrality marker error " << std::endl;
            return parsekey::FAIL;
         }
         integral_cols = !integral_cols;

         continue;
      }

      // new column?
      if( !( word_ref == colname ) )
      {
         if( word_ref.empty() ) // empty line
            continue;

         colname = word_ref.to_string();
         auto ret = colname2idx.emplace( colname, ncols++ );
         colnames.push_back( colname );

         if( !ret.second )
         {
            std::cerr << "duplicate column " << std::endl;
            return parsekey::FAIL;
         }

         assert( lb4cols.size() == col_flags.size() );

         col_flags.emplace_back( integral_cols ? ColFlag::INTEGRAL
                                               : ColFlag::NONE );

         // initialize with default bounds
         if( integral_cols )
         {
            lb4cols.push_back( REAL{0.0} );
            ub4cols.push_back( REAL{1.0} );
         }
         else
         {
            lb4cols.push_back( REAL{0.0} );
            ub4cols.push_back( REAL{0.0} );
            col_flags.back().set( ColFlag::UB_INF );
         }

         assert( col_flags.size() == lb4cols.size() );

         if( ncols > 1 )
            pdqsort( entries.begin() + colstart, entries.end(),
                     []( Triplet<REAL> a, Triplet<REAL> b ) {
                        return std::get<1>( b ) > std::get<1>( a );
                     } );

         colstart = entries.size();
      }

      assert( ncols > 0 );

      if( !qi::phrase_parse(
              it, strline.end(),
              +( qi::lexeme[qi::as_string[+qi::graph][( parsename )]] >>
                 qi::real_parser<typename RealParseType<REAL>::type>()[(
                     addtuple )] ),
              ascii::space ) )
         return parsekey::FAIL;
   }

   return parsekey::FAIL;
}

template <typename REAL>
typename MpsParser<REAL>::parsekey
MpsParser<REAL>::parseRanges( boost::iostreams::filtering_istream& file )
{
   using namespace boost::spirit;
   std::string strline;
   assert( rowrhs.size() == rowlhs.size() );

   while( getline( file, strline ) )
   {
      std::string::iterator it;
      boost::string_ref word_ref;
      MpsParser<REAL>::parsekey key = checkFirstWord( strline, it, word_ref );

      // start of new section?
      if( key != parsekey::NONE && key != parsekey::RANGES )
         return key;

      if( word_ref.empty() )
         continue;

      int rowidx;

      auto parsename = [&rowidx, this]( std::string name ) {
         auto mit = rowname2idx.find( name );

         assert( mit != rowname2idx.end() );
         rowidx = mit->second;

         assert( rowidx >= 0 && rowidx < nRows );
      };

      auto addrange = [&rowidx,
                       this]( typename RealParseType<REAL>::type val ) {
         assert( size_t( rowidx ) < rowrhs.size() );

         if( row_type[rowidx] == boundtype::GE )
         {
            row_flags[rowidx].unset( RowFlag::RHS_INF );
            rowrhs[rowidx] = rowlhs[rowidx] + abs( val );
         }
         else if( row_type[rowidx] == boundtype::LE )
         {
            row_flags[rowidx].unset( RowFlag::LHS_INF );
            rowlhs[rowidx] = rowrhs[rowidx] - abs( val );
         }
         else
         {
            assert( row_type[rowidx] == boundtype::EQ );
            assert( rowrhs[rowidx] == rowlhs[rowidx] );

            if( val > REAL{0.0} )
               rowrhs[rowidx] = rowrhs[rowidx] + val;
            else if( val < REAL{0.0} )
               rowlhs[rowidx] = rowlhs[rowidx] + val;
         }
      };

      // compulsory part
      if( !qi::phrase_parse(
              it, strline.end(),
              +( qi::lexeme[qi::as_string[+qi::graph][( parsename )]] >>
                 qi::real_parser<typename RealParseType<REAL>::type>()[(
                     addrange )] ),
              ascii::space ) )
         return parsekey::FAIL;

      // optional part todo don't replicate code
      qi::phrase_parse(
          it, strline.end(),
          +( qi::lexeme[qi::as_string[+qi::graph][( parsename )]] >>
             qi::real_parser<typename RealParseType<REAL>::type>()[(
                 addrange )] ),
          ascii::space );
   }

   return parsekey::FAIL;
}

template <typename REAL>
typename MpsParser<REAL>::parsekey
MpsParser<REAL>::parseRhs( boost::iostreams::filtering_istream& file )
{
   using namespace boost::spirit;
   std::string strline;

   while( getline( file, strline ) )
   {
      std::string::iterator it;
      boost::string_ref word_ref;
      MpsParser<REAL>::parsekey key = checkFirstWord( strline, it, word_ref );

      // start of new section?
      if( key != parsekey::NONE && key != parsekey::RHS )
         return key;

      if( word_ref.empty() )
         continue;

      int rowidx;

      auto parsename = [&rowidx, this]( std::string name ) {
         auto mit = rowname2idx.find( name );

         assert( mit != rowname2idx.end() );
         rowidx = mit->second;

         assert( rowidx >= -1 );
         assert( rowidx < nRows );
      };

      auto addrhs = [&rowidx, this]( typename RealParseType<REAL>::type val ) {
         if( rowidx == -1 )
         {
            objoffset = -REAL{val};
            return;
         }
         if( row_type[rowidx] == boundtype::EQ ||
             row_type[rowidx] == boundtype::LE )
         {
            assert( size_t( rowidx ) < rowrhs.size() );
            rowrhs[rowidx] = REAL{val};
            row_flags[rowidx].unset( RowFlag::RHS_INF );
         }

         if( row_type[rowidx] == boundtype::EQ ||
             row_type[rowidx] == boundtype::GE )
         {
            assert( size_t( rowidx ) < rowlhs.size() );
            rowlhs[rowidx] = REAL{val};
            row_flags[rowidx].unset( RowFlag::LHS_INF );
         }
      };

      if( !qi::phrase_parse(
              it, strline.end(),
              +( qi::lexeme[qi::as_string[+qi::graph][( parsename )]] >>
                 qi::real_parser<typename RealParseType<REAL>::type>()[(
                     addrhs )] ),
              ascii::space ) )
         return parsekey::FAIL;
   }

   return parsekey::FAIL;
}

template <typename REAL>
typename MpsParser<REAL>::parsekey
MpsParser<REAL>::parseBounds( boost::iostreams::filtering_istream& file )
{
   using namespace boost::spirit;
   std::string strline;

   Vec<bool> ub_is_default( lb4cols.size(), true );
   Vec<bool> lb_is_default( lb4cols.size(), true );

   while( getline( file, strline ) )
   {
      std::string::iterator it;
      boost::string_ref word_ref;
      MpsParser<REAL>::parsekey key = checkFirstWord( strline, it, word_ref );

      // start of new section?
      if( key != parsekey::NONE )
         return key;

      if( word_ref.empty() )
         continue;

      bool islb = false;
      bool isub = false;
      bool isintegral = false;
      bool isdefaultbound = false;

      if( word_ref == "UP" ) // lower bound
         isub = true;
      else if( word_ref == "LO" ) // upper bound
         islb = true;
      else if( word_ref == "FX" ) // fixed
      {
         islb = true;
         isub = true;
      }
      else if( word_ref == "MI" ) // infinite lower bound
      {
         islb = true;
         isdefaultbound = true;
      }
      else if( word_ref == "PL" ) // infinite upper bound (redundant)
      {
         isub = true;
         isdefaultbound = true;
      }
      else if( word_ref == "BV" ) // binary
      {
         isintegral = true;
         isdefaultbound = true;
         islb = true;
         isub = true;
      }
      else if( word_ref == "LI" ) // integer lower bound
      {
         islb = true;
         isintegral = true;
      }
      else if( word_ref == "UI" ) // integer upper bound
      {
         isub = true;
         isintegral = true;
      }
      else if( word_ref == "FR" ) // free variable
      {
         islb = true;
         isub = true;
         isdefaultbound = true;
      }
      else
      {
         std::cerr << "unknown bound type " << word_ref << std::endl;
         exit( 1 );
      }

      // parse over next word
      qi::phrase_parse( it, strline.end(), qi::lexeme[+qi::graph],
                        ascii::space );

      int colidx;

      auto parsename = [&colidx, this]( std::string name ) {
         auto mit = colname2idx.find( name );
         assert( mit != colname2idx.end() );
         colidx = mit->second;
         assert( colidx >= 0 );
      };

      if( isdefaultbound )
      {
         if( !qi::phrase_parse(
                 it, strline.end(),
                 ( qi::lexeme[qi::as_string[+qi::graph][( parsename )]] ),
                 ascii::space ) )
            return parsekey::FAIL;

         if( isintegral ) // binary
         {
            if( islb )
               lb4cols[colidx] = REAL{0.0};
            if( isub )
            {
               col_flags[colidx].unset( ColFlag::UB_INF );
               ub4cols[colidx] = REAL{1.0};
            }
            col_flags[colidx].set( ColFlag::INTEGRAL );
         }
         else
         {
            if( islb )
               col_flags[colidx].set( ColFlag::LB_INF );
            if( isub )
               col_flags[colidx].set( ColFlag::UB_INF );
         }
         continue;
      }

      if( !qi::phrase_parse(
              it, strline.end(),
              +( qi::lexeme[qi::as_string[+qi::graph][( parsename )]] >>
                 qi::real_parser<typename RealParseType<REAL>::type>()[(
                     [&ub_is_default, &lb_is_default, &colidx, &islb, &isub,
                      &isintegral,
                      this]( typename RealParseType<REAL>::type val ) {
                        if( islb )
                        {
                           lb4cols[colidx] = REAL{val};
                           lb_is_default[colidx] = false;
                           col_flags[colidx].unset( ColFlag::LB_INF );
                        }
                        if( isub )
                        {
                           ub4cols[colidx] = REAL{val};
                           ub_is_default[colidx] = false;
                           col_flags[colidx].unset( ColFlag::UB_INF );
                        }

                        if( isintegral )
                           col_flags[colidx].set( ColFlag::INTEGRAL );

                        if( col_flags[colidx].test( ColFlag::INTEGRAL ) )
                        {
                           col_flags[colidx].set( ColFlag::INTEGRAL );
                           if( !islb && lb_is_default[colidx] )
                              lb4cols[colidx] = REAL{0.0};
                           if( !isub && ub_is_default[colidx] )
                              col_flags[colidx].set( ColFlag::UB_INF );
                        }
                     } )] ),
              ascii::space ) )
         return parsekey::FAIL;
   }

   return parsekey::FAIL;
}

template <typename REAL>
bool
MpsParser<REAL>::parseFile( const std::string& filename )
{
   std::ifstream file( filename, std::ifstream::in );
   boost::iostreams::filtering_istream in;

   if( !file )
      return false;

   if( boost::algorithm::ends_with( filename, ".gz" ) )
      in.push( boost::iostreams::gzip_decompressor() );
   else if( boost::algorithm::ends_with( filename, ".bz2" ) )
      in.push( boost::iostreams::bzip2_decompressor() );

   in.push( file );

   parse( in );

   return true;
}

template <typename REAL>
void
MpsParser<REAL>::parse( boost::iostreams::filtering_istream& file )
{
   nnz = 0;
   parsekey keyword = parsekey::NONE;
   parsekey keyword_old = parsekey::NONE;

   // parsing loop
   while( keyword != parsekey::FAIL && keyword != parsekey::END )
   {
      keyword_old = keyword;
      switch( keyword )
      {
      case parsekey::ROWS:
         keyword = parseRows( file, row_type );
         break;
      case parsekey::COLS:
         keyword = parseCols( file, row_type );
         break;
      case parsekey::RHS:
         keyword = parseRhs( file );
         break;
      case parsekey::RANGES:
         keyword = parseRanges( file );
         break;
      case parsekey::BOUNDS:
         keyword = parseBounds( file );
         break;
      case parsekey::FAIL:
         break;
      default:
         keyword = parseDefault( file );
         break;
      }
   }

   if( keyword == parsekey::FAIL )
   {
      printErrorMessage( keyword_old );
      exit( 1 ); // todo exception
   }

   assert( row_type.size() == unsigned( nRows ) );

   nCols = colname2idx.size();
   nRows = rowname2idx.size() - 1; // subtract obj row
}

} // namespace papilo

#endif /* _PARSING_MPS_PARSER_HPP_ */
