﻿# CMakeList.txt : projet CMake pour 2D_Bin_Packing, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

project ("2D_Bin_Packing")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (2D_Bin_Packing "src/2DBinPacking.cpp" "src/2DBinPacking.h" "src/Bin.h" "src/Bin.cpp" "src/Rect.h" "src/Rect.cpp" "src/IOUtils.h" "src/IOUtils.cpp" "src/FileData.cpp" "src/GeneticAlgorithm.h" "src/GeneticAlgorithm.cpp" "src/Tools.h" "src/Tools.cpp" "src/Bin2.h" "src/Bin2.cpp" "src/NFDHAlgorithm.h" "src/NFDHAlgorithm.cpp" "src/SimulatedAnnealing.h" "src/SimulatedAnnealing.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 2D_Bin_Packing PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
