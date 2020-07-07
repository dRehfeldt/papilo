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

#ifndef PAPILO_TEST_INSTANCES_GT2
#define PAPILO_TEST_INSTANCES_GT2

#include "papilo/core/Problem.hpp"
#include "papilo/core/ProblemBuilder.hpp"

namespace papilo
{
namespace instances
{

Problem<double>
gt2()
{
   /// PROBLEM BUILDER CODE
   Vec<double> coeffobj{
       3595.0, 3595.0, 1833.0, 3595.0, 3595.0, 3595.0, 1833.0, 3595.0, 3100.0,
       3100.0, 1257.0, 3100.0, 1355.0, 7797.0, 3100.0, 3100.0, 1257.0, 3100.0,
       1355.0, 7797.0, 2685.0, 2685.0, 1257.0, 2685.0, 1176.0, 6214.0, 2685.0,
       2685.0, 1257.0, 2685.0, 1176.0, 6214.0, 2940.0, 2940.0, 1980.0, 2940.0,
       1980.0, 7145.0, 2940.0, 2940.0, 1980.0, 2940.0, 1980.0, 7145.0, 3100.0,
       3100.0, 1816.0, 3100.0, 1926.0, 7011.0, 3100.0, 3100.0, 1816.0, 3100.0,
       1926.0, 7011.0, 3100.0, 3100.0, 1816.0, 3100.0, 1983.0, 7797.0, 3100.0,
       3100.0, 1816.0, 3100.0, 1983.0, 7797.0, 1926.0, 7011.0, 1926.0, 7011.0,
       3100.0, 3100.0, 1257.0, 3100.0, 3100.0, 3100.0, 1257.0, 3100.0, 2448.0,
       2448.0, 1652.0, 2448.0, 1652.0, 5954.0, 2448.0, 2448.0, 1652.0, 2448.0,
       1652.0, 5954.0, 0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
       0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,    0.0,
   };
   Vec<double> lbs{
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
   };
   Vec<bool> lbInf{
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false,
   };
   Vec<double> ubs{
       9.0,  9.0,  9.0,  9.0,  9.0,  9.0,  9.0,  9.0,  15.0, 15.0, 15.0, 15.0,
       15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 14.0, 14.0, 14.0, 14.0,
       14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 1.0,  1.0,  1.0,  1.0,
       1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  6.0,  6.0,  6.0,  6.0,
       6.0,  6.0,  6.0,  6.0,  6.0,  6.0,  6.0,  6.0,  8.0,  8.0,  8.0,  8.0,
       8.0,  8.0,  8.0,  8.0,  8.0,  8.0,  8.0,  8.0,  5.0,  5.0,  5.0,  5.0,
       12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 12.0, 5.0,  5.0,  5.0,  5.0,
       5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  6.0,  4.0,  9.0,  5.0,
       4.0,  2.0,  2.0,  1.0,  6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,
       6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,  6.0,  4.0,  9.0,  5.0,
       4.0,  2.0,  2.0,  1.0,  6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,
       6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,  6.0,  4.0,  9.0,  5.0,
       4.0,  2.0,  2.0,  1.0,  6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,
       6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,  6.0,  4.0,  9.0,  5.0,
       4.0,  2.0,  2.0,  1.0,  6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,
       6.0,  4.0,  9.0,  5.0,  4.0,  2.0,  2.0,  1.0,
   };
   Vec<bool> ubInf{
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false,
   };
   Vec<bool> isIntegral{
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true, true, true, true, true,
       true, true, true, true, true, true, true, true,
   };
   Vec<bool> lhsIsInf{
       false, false, false, false, false, false, false, false, false, false,
       false, false, true,  true,  true,  true,  true,  true,  true,  true,
       true,  true,  true,  true,  true,  true,  true,  true,  true,
   };
   Vec<double> lhs{
       200.0, 80.0, 300.0, 250.0, 61.0, 6064.0, 94.0, 67.0, 450.0, 231.0,
       76.0,  0.0,  0.0,   0.0,   0.0,  0.0,    0.0,  0.0,  0.0,   0.0,
       0.0,   0.0,  0.0,   0.0,   0.0,  0.0,    0.0,  0.0,  0.0,
   };
   Vec<bool> rhsIsInf{
       true,  true,  true,  true,  true,  true,  true,  true,  true,  true,
       true,  true,  false, false, false, false, false, false, false, false,
       false, false, false, false, false, false, false, false, false,
   };
   Vec<double> rhs{
       0.0, 0.0, 0.0, 0.0,  0.0,  0.0, 0.0, 0.0, 0.0, 0.0,
       0.0, 0.0, 9.0, 15.0, 14.0, 1.0, 6.0, 8.0, 5.0, 12.0,
       5.0, 6.0, 4.0, 9.0,  5.0,  4.0, 2.0, 2.0, 1.0,
   };
   Vec<std::tuple<int, int, double>> entries{
       { 0, 0, 50.0 },    { 0, 8, 45.0 },    { 0, 20, 40.0 },
       { 0, 32, 30.0 },   { 0, 44, 32.0 },   { 0, 56, 50.0 },
       { 0, 72, 45.0 },   { 0, 80, 2534.0 }, { 0, 92, 22.0 },
       { 0, 93, 56.0 },   { 0, 94, 30.0 },   { 0, 95, 30.0 },
       { 0, 96, 23.0 },   { 0, 97, 42.0 },   { 0, 98, 56.0 },
       { 0, 99, 28.0 },   { 1, 1, 50.0 },    { 1, 9, 45.0 },
       { 1, 21, 40.0 },   { 1, 33, 30.0 },   { 1, 45, 32.0 },
       { 1, 57, 50.0 },   { 1, 73, 45.0 },   { 1, 81, 2534.0 },
       { 1, 100, 22.0 },  { 1, 101, 56.0 },  { 1, 102, 30.0 },
       { 1, 103, 30.0 },  { 1, 104, 23.0 },  { 1, 105, 42.0 },
       { 1, 106, 56.0 },  { 1, 107, 28.0 },  { 2, 2, 50.0 },
       { 2, 10, 45.0 },   { 2, 22, 40.0 },   { 2, 34, 30.0 },
       { 2, 46, 32.0 },   { 2, 58, 50.0 },   { 2, 74, 45.0 },
       { 2, 82, 2534.0 }, { 2, 108, 22.0 },  { 2, 109, 56.0 },
       { 2, 110, 30.0 },  { 2, 111, 30.0 },  { 2, 112, 23.0 },
       { 2, 113, 42.0 },  { 2, 114, 56.0 },  { 2, 115, 28.0 },
       { 3, 3, 50.0 },    { 3, 11, 45.0 },   { 3, 23, 40.0 },
       { 3, 35, 30.0 },   { 3, 47, 32.0 },   { 3, 59, 52.0 },
       { 3, 75, 44.0 },   { 3, 83, 2534.0 }, { 3, 116, 22.0 },
       { 3, 117, 56.0 },  { 3, 118, 30.0 },  { 3, 119, 30.0 },
       { 3, 120, 23.0 },  { 3, 121, 42.0 },  { 3, 122, 56.0 },
       { 3, 123, 28.0 },  { 4, 12, 28.0 },   { 4, 24, 45.0 },
       { 4, 36, 16.5 },   { 4, 48, 45.0 },   { 4, 60, 52.0 },
       { 4, 68, 45.0 },   { 4, 84, 2519.0 }, { 4, 124, 25.0 },
       { 4, 125, 34.0 },  { 4, 126, 25.0 },  { 4, 127, 19.0 },
       { 4, 128, 56.0 },  { 4, 129, 34.0 },  { 4, 130, 34.0 },
       { 4, 131, 25.0 },  { 5, 13, 28.0 },   { 5, 25, 45.0 },
       { 5, 37, 16.5 },   { 5, 49, 45.0 },   { 5, 61, 52.0 },
       { 5, 69, 45.0 },   { 5, 85, 2519.0 }, { 5, 132, 25.0 },
       { 5, 133, 34.0 },  { 5, 134, 25.0 },  { 5, 135, 19.0 },
       { 5, 136, 56.0 },  { 5, 137, 34.0 },  { 5, 138, 34.0 },
       { 5, 139, 25.0 },  { 6, 4, 50.0 },    { 6, 14, 45.0 },
       { 6, 26, 40.0 },   { 6, 38, 30.0 },   { 6, 50, 32.0 },
       { 6, 62, 50.0 },   { 6, 76, 45.0 },   { 6, 86, 2534.0 },
       { 6, 140, 22.0 },  { 6, 141, 56.0 },  { 6, 142, 30.0 },
       { 6, 143, 30.0 },  { 6, 144, 23.0 },  { 6, 145, 42.0 },
       { 6, 146, 56.0 },  { 6, 147, 28.0 },  { 7, 5, 50.0 },
       { 7, 15, 45.0 },   { 7, 27, 40.0 },   { 7, 39, 30.0 },
       { 7, 51, 32.0 },   { 7, 63, 50.0 },   { 7, 77, 45.0 },
       { 7, 87, 2534.0 }, { 7, 148, 22.0 },  { 7, 149, 56.0 },
       { 7, 150, 30.0 },  { 7, 151, 30.0 },  { 7, 152, 23.0 },
       { 7, 153, 42.0 },  { 7, 154, 56.0 },  { 7, 155, 28.0 },
       { 8, 6, 50.0 },    { 8, 16, 45.0 },   { 8, 28, 40.0 },
       { 8, 40, 30.0 },   { 8, 52, 32.0 },   { 8, 64, 50.0 },
       { 8, 78, 45.0 },   { 8, 88, 2534.0 }, { 8, 156, 22.0 },
       { 8, 157, 56.0 },  { 8, 158, 30.0 },  { 8, 159, 30.0 },
       { 8, 160, 23.0 },  { 8, 161, 42.0 },  { 8, 162, 56.0 },
       { 8, 163, 28.0 },  { 9, 7, 50.0 },    { 9, 17, 45.0 },
       { 9, 29, 40.0 },   { 9, 41, 30.0 },   { 9, 53, 32.0 },
       { 9, 65, 52.0 },   { 9, 79, 44.0 },   { 9, 89, 2534.0 },
       { 9, 164, 22.0 },  { 9, 165, 56.0 },  { 9, 166, 30.0 },
       { 9, 167, 30.0 },  { 9, 168, 23.0 },  { 9, 169, 42.0 },
       { 9, 170, 56.0 },  { 9, 171, 28.0 },  { 10, 18, 28.0 },
       { 10, 30, 45.0 },  { 10, 42, 16.5 },  { 10, 54, 45.0 },
       { 10, 66, 52.0 },  { 10, 70, 45.0 },  { 10, 90, 2519.0 },
       { 10, 172, 25.0 }, { 10, 173, 34.0 }, { 10, 174, 25.0 },
       { 10, 175, 19.0 }, { 10, 176, 56.0 }, { 10, 177, 34.0 },
       { 10, 178, 34.0 }, { 10, 179, 25.0 }, { 11, 19, 28.0 },
       { 11, 31, 45.0 },  { 11, 43, 16.5 },  { 11, 55, 45.0 },
       { 11, 67, 52.0 },  { 11, 71, 45.0 },  { 11, 91, 2519.0 },
       { 11, 180, 25.0 }, { 11, 181, 34.0 }, { 11, 182, 25.0 },
       { 11, 183, 19.0 }, { 11, 184, 56.0 }, { 11, 185, 34.0 },
       { 11, 186, 34.0 }, { 11, 187, 25.0 }, { 12, 0, 1.0 },
       { 12, 1, 1.0 },    { 12, 2, 1.0 },    { 12, 3, 1.0 },
       { 12, 4, 1.0 },    { 12, 5, 1.0 },    { 12, 6, 1.0 },
       { 12, 7, 1.0 },    { 13, 8, 1.0 },    { 13, 9, 1.0 },
       { 13, 10, 1.0 },   { 13, 11, 1.0 },   { 13, 12, 1.0 },
       { 13, 13, 1.0 },   { 13, 14, 1.0 },   { 13, 15, 1.0 },
       { 13, 16, 1.0 },   { 13, 17, 1.0 },   { 13, 18, 1.0 },
       { 13, 19, 1.0 },   { 14, 20, 1.0 },   { 14, 21, 1.0 },
       { 14, 22, 1.0 },   { 14, 23, 1.0 },   { 14, 24, 1.0 },
       { 14, 25, 1.0 },   { 14, 26, 1.0 },   { 14, 27, 1.0 },
       { 14, 28, 1.0 },   { 14, 29, 1.0 },   { 14, 30, 1.0 },
       { 14, 31, 1.0 },   { 15, 32, 1.0 },   { 15, 33, 1.0 },
       { 15, 34, 1.0 },   { 15, 35, 1.0 },   { 15, 36, 1.0 },
       { 15, 37, 1.0 },   { 15, 38, 1.0 },   { 15, 39, 1.0 },
       { 15, 40, 1.0 },   { 15, 41, 1.0 },   { 15, 42, 1.0 },
       { 15, 43, 1.0 },   { 16, 44, 1.0 },   { 16, 45, 1.0 },
       { 16, 46, 1.0 },   { 16, 47, 1.0 },   { 16, 48, 1.0 },
       { 16, 49, 1.0 },   { 16, 50, 1.0 },   { 16, 51, 1.0 },
       { 16, 52, 1.0 },   { 16, 53, 1.0 },   { 16, 54, 1.0 },
       { 16, 55, 1.0 },   { 17, 56, 1.0 },   { 17, 57, 1.0 },
       { 17, 58, 1.0 },   { 17, 59, 1.0 },   { 17, 60, 1.0 },
       { 17, 61, 1.0 },   { 17, 62, 1.0 },   { 17, 63, 1.0 },
       { 17, 64, 1.0 },   { 17, 65, 1.0 },   { 17, 66, 1.0 },
       { 17, 67, 1.0 },   { 18, 68, 1.0 },   { 18, 69, 1.0 },
       { 18, 70, 1.0 },   { 18, 71, 1.0 },   { 19, 72, 1.0 },
       { 19, 73, 1.0 },   { 19, 74, 1.0 },   { 19, 75, 1.0 },
       { 19, 76, 1.0 },   { 19, 77, 1.0 },   { 19, 78, 1.0 },
       { 19, 79, 1.0 },   { 20, 80, 1.0 },   { 20, 81, 1.0 },
       { 20, 82, 1.0 },   { 20, 83, 1.0 },   { 20, 84, 1.0 },
       { 20, 85, 1.0 },   { 20, 86, 1.0 },   { 20, 87, 1.0 },
       { 20, 88, 1.0 },   { 20, 89, 1.0 },   { 20, 90, 1.0 },
       { 20, 91, 1.0 },   { 21, 92, 1.0 },   { 21, 100, 1.0 },
       { 21, 108, 1.0 },  { 21, 116, 1.0 },  { 21, 124, 1.0 },
       { 21, 132, 1.0 },  { 21, 140, 1.0 },  { 21, 148, 1.0 },
       { 21, 156, 1.0 },  { 21, 164, 1.0 },  { 21, 172, 1.0 },
       { 21, 180, 1.0 },  { 22, 93, 1.0 },   { 22, 101, 1.0 },
       { 22, 109, 1.0 },  { 22, 117, 1.0 },  { 22, 125, 1.0 },
       { 22, 133, 1.0 },  { 22, 141, 1.0 },  { 22, 149, 1.0 },
       { 22, 157, 1.0 },  { 22, 165, 1.0 },  { 22, 173, 1.0 },
       { 22, 181, 1.0 },  { 23, 94, 1.0 },   { 23, 102, 1.0 },
       { 23, 110, 1.0 },  { 23, 118, 1.0 },  { 23, 126, 1.0 },
       { 23, 134, 1.0 },  { 23, 142, 1.0 },  { 23, 150, 1.0 },
       { 23, 158, 1.0 },  { 23, 166, 1.0 },  { 23, 174, 1.0 },
       { 23, 182, 1.0 },  { 24, 95, 1.0 },   { 24, 103, 1.0 },
       { 24, 111, 1.0 },  { 24, 119, 1.0 },  { 24, 127, 1.0 },
       { 24, 135, 1.0 },  { 24, 143, 1.0 },  { 24, 151, 1.0 },
       { 24, 159, 1.0 },  { 24, 167, 1.0 },  { 24, 175, 1.0 },
       { 24, 183, 1.0 },  { 25, 96, 1.0 },   { 25, 104, 1.0 },
       { 25, 112, 1.0 },  { 25, 120, 1.0 },  { 25, 128, 1.0 },
       { 25, 136, 1.0 },  { 25, 144, 1.0 },  { 25, 152, 1.0 },
       { 25, 160, 1.0 },  { 25, 168, 1.0 },  { 25, 176, 1.0 },
       { 25, 184, 1.0 },  { 26, 97, 1.0 },   { 26, 105, 1.0 },
       { 26, 113, 1.0 },  { 26, 121, 1.0 },  { 26, 129, 1.0 },
       { 26, 137, 1.0 },  { 26, 145, 1.0 },  { 26, 153, 1.0 },
       { 26, 161, 1.0 },  { 26, 169, 1.0 },  { 26, 177, 1.0 },
       { 26, 185, 1.0 },  { 27, 98, 1.0 },   { 27, 106, 1.0 },
       { 27, 114, 1.0 },  { 27, 122, 1.0 },  { 27, 130, 1.0 },
       { 27, 138, 1.0 },  { 27, 146, 1.0 },  { 27, 154, 1.0 },
       { 27, 162, 1.0 },  { 27, 170, 1.0 },  { 27, 178, 1.0 },
       { 27, 186, 1.0 },  { 28, 99, 1.0 },   { 28, 107, 1.0 },
       { 28, 115, 1.0 },  { 28, 123, 1.0 },  { 28, 131, 1.0 },
       { 28, 139, 1.0 },  { 28, 147, 1.0 },  { 28, 155, 1.0 },
       { 28, 163, 1.0 },  { 28, 171, 1.0 },  { 28, 179, 1.0 },
       { 28, 187, 1.0 },
   };
   Vec<std::string> rnames{
       "dem...01", "dem...02", "dem...03", "dem...04", "dem...05", "dem...06",
       "dem...07", "dem...08", "dem...09", "dem...10", "dem...11", "dem...12",
       "avail.01", "avail.02", "avail.03", "avail.04", "avail.05", "avail.06",
       "avail.07", "avail.08", "avail.09", "avail.10", "avail.11", "avail.12",
       "avail.13", "avail.14", "avail.15", "avail.16", "avail.17",
   };
   Vec<std::string> cnames{
       "x...0101", "x...0201", "x...0301", "x...0401", "x...0701", "x...0801",
       "x...0901", "x...1001", "x...0102", "x...0202", "x...0302", "x...0402",
       "x...0502", "x...0602", "x...0702", "x...0802", "x...0902", "x...1002",
       "x...1102", "x...1202", "x...0103", "x...0203", "x...0303", "x...0403",
       "x...0503", "x...0603", "x...0703", "x...0803", "x...0903", "x...1003",
       "x...1103", "x...1203", "x...0104", "x...0204", "x...0304", "x...0404",
       "x...0504", "x...0604", "x...0704", "x...0804", "x...0904", "x...1004",
       "x...1104", "x...1204", "x...0105", "x...0205", "x...0305", "x...0405",
       "x...0505", "x...0605", "x...0705", "x...0805", "x...0905", "x...1005",
       "x...1105", "x...1205", "x...0106", "x...0206", "x...0306", "x...0406",
       "x...0506", "x...0606", "x...0706", "x...0806", "x...0906", "x...1006",
       "x...1106", "x...1206", "x...0507", "x...0607", "x...1107", "x...1207",
       "x...0108", "x...0208", "x...0308", "x...0408", "x...0708", "x...0808",
       "x...0908", "x...1008", "x...0109", "x...0209", "x...0309", "x...0409",
       "x...0509", "x...0609", "x...0709", "x...0809", "x...0909", "x...1009",
       "x...1109", "x...1209", "x...0110", "x...0111", "x...0112", "x...0113",
       "x...0114", "x...0115", "x...0116", "x...0117", "x...0210", "x...0211",
       "x...0212", "x...0213", "x...0214", "x...0215", "x...0216", "x...0217",
       "x...0310", "x...0311", "x...0312", "x...0313", "x...0314", "x...0315",
       "x...0316", "x...0317", "x...0410", "x...0411", "x...0412", "x...0413",
       "x...0414", "x...0415", "x...0416", "x...0417", "x...0510", "x...0511",
       "x...0512", "x...0513", "x...0514", "x...0515", "x...0516", "x...0517",
       "x...0610", "x...0611", "x...0612", "x...0613", "x...0614", "x...0615",
       "x...0616", "x...0617", "x...0710", "x...0711", "x...0712", "x...0713",
       "x...0714", "x...0715", "x...0716", "x...0717", "x...0810", "x...0811",
       "x...0812", "x...0813", "x...0814", "x...0815", "x...0816", "x...0817",
       "x...0910", "x...0911", "x...0912", "x...0913", "x...0914", "x...0915",
       "x...0916", "x...0917", "x...1010", "x...1011", "x...1012", "x...1013",
       "x...1014", "x...1015", "x...1016", "x...1017", "x...1110", "x...1111",
       "x...1112", "x...1113", "x...1114", "x...1115", "x...1116", "x...1117",
       "x...1210", "x...1211", "x...1212", "x...1213", "x...1214", "x...1215",
       "x...1216", "x...1217",
   };
   int nCols = 188;
   int nRows = 29;
   ProblemBuilder<double> pb;
   pb.reserve( 376, 29, 188 );
   pb.setNumRows( nRows );
   pb.setNumCols( nCols );
   pb.setObjAll( coeffobj );
   pb.setObjOffset( 0.0 );
   pb.setColLbAll( lbs );
   pb.setColLbInfAll( lbInf );
   pb.setColUbAll( ubs );
   pb.setColUbInfAll( ubInf );
   pb.setColIntegralAll( isIntegral );
   pb.setRowLhsInfAll( lhsIsInf );
   pb.setRowRhsInfAll( rhsIsInf );
   pb.setRowLhsAll( lhs );
   pb.setRowRhsAll( rhs );
   pb.setRowNameAll( rnames );
   pb.addEntryAll( entries );
   pb.setColNameAll( cnames );
   pb.setProblemName( "gt2.hpp" );
   Problem<double> problem = pb.build();
   /// PROBLEM BUILDER CODE END

   return problem;
}

} // namespace instances
} // namespace papilo

#endif
