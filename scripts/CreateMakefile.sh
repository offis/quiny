#!/bin/tcsh
# $Id: CreateMakefile.sh 716 2005-12-20 13:49:04Z claus $
# $Log$
# Revision 1.1  2004/10/01 07:29:17  thorsten
# This script creates makefiles, given the sources and include paths (and
# optional libraries). The created Makefile should be understood by any
# make).
#
# Revision 1.4  2004/07/16 14:05:17  thorsten
# Removed mkdir of the object directory.
# Fixed bug in the handling of linker commands.
#
# Revision 1.3  2004/04/29 13:16:33  ramon
# Worked abit on the release-rule and ensured the availibility of the object-
# directories for compilations.
#
# Revision 1.2  2004/02/25 15:13:57  thorsten
# Workaround for shell limitations (hit when there are "too many"
# dependencies).
# Added the inclusion of additional object files and libraries into the
# dependency list.
#
# Revision 1.1  2004/02/10 16:34:59  thorsten
# Automatic generation of makefiles.
#

if ( $# == 0) then

  echo USAGE: CreateMakefile.sh INCLUDES \<IncludeDirs\>\* SOURCES \<Sources\>+ COMPILER_OPTS \<CompileOptions\>\* OBJECT_DIR \<ObjectDir\> OUTPUT_FILE \[\<OutputFile\>\] LINKER_OPTS \[\<LinkerOpts\>\] MAKEFILE \<MakefileName\>
  echo ""
  echo \<Value\>\* denotes a \(possibliy empty\) list, \<Value\>\+ denotes non-empty list,  
  echo \[\<Value\>\] an optional argument. 
  echo ""
  echo \<IncludeDirs\>\* is a list of paths to directories containing necessary header 
  echo "              " files.
  echo \<Sources\>+ is a list of C++ source files.
  echo \<CompileOptions\>+ is a list of options for the compilation of each source file.
  echo \<ObjectDir\> is a path to a directory where the objects files will be placed.
  echo \<OutputFile\> determines the kind of output. If the name ends with \".a\"
  echo "            " the object files will be ar\'ed to library. If this option is 
  echo "            " omitted there will be no linking \(just compilation\). Otherwise
  echo "            " the files will be linked to an executable.
  echo \<LinkerOpts\> options passed to the linker \(or ar in case of a library\)
  echo \<Makefile\> is the name of the generated makefile
  exit -1

endif

setenv PATH /bin:$PATH

# parse command line

# 1. get includes
set IncludeDirs = 
if (`echo $1` == "INCLUDES") then
  shift
  while (`echo $1` != "SOURCES")
      set IncludeDirs=($IncludeDirs $1)
      shift
  end
endif

# 2. get sources
set SOURCE_FILES = 
shift

while (`echo $1` != "COMPILER_OPTS")
    set SOURCE_FILES=($SOURCE_FILES $1)
    shift
end
  
#3. get compiler options
set CompilerOpts = 
set CompilerDefines =
shift
while (`echo $1` != "OBJECT_DIR")
  set CompilerOpts=($CompilerOpts $1)
  if (`echo $1 | grep "^-D"` != "") then
    set CompilerDefines=($CompilerDefines $1)
  endif
  shift
end

#4. get object dir
shift
set ObjectDir = $1
shift

#5. output file
set OutputFile = 
shift
if (`echo $1` != "LINKER_OPTS") then
  set OutputFile = $1
  shift
endif

#6. linker options
set LinkerOpts =
shift
while (`echo $1` != "MAKEFILE")
  set LinkerOpts=($LinkerOpts $1)
  shift
end

# Makefile name
shift
set OutputMakefile = $1

# display include directories
if ($#IncludeDirs == 0) then

  echo WARNING: No include directories!

else

  echo Include directories: 

  foreach incDir ($IncludeDirs)
    echo "    " $incDir
  end
  
endif  

echo ""

# display compiler options
if ($#CompilerOpts == 0) then

  echo WARNING: No compiler options were given.

else

  echo Compiler options: 

  foreach compilerOpt ($CompilerOpts)
    echo "    " $compilerOpt
  end
  
endif  


# basenames without extension
#set BASENAMES = `echo $SOURCE_FILES:t:r`
# keep path
#set BASENAMES = `echo $SOURCE_FILES:r`
set BASENAMES =
foreach sourceFile ($SOURCE_FILES)
  set BASENAMES = ($BASENAMES $sourceFile:r)
end

# create object file names
set OBJECTS =
foreach baseName ($BASENAMES)
  set OBJECTS = ($OBJECTS $ObjectDir/$baseName.o)
end

#create include options
set INCLUDE_OPTS =
foreach includePath ($IncludeDirs)
  set INCLUDE_OPTS = ($INCLUDE_OPTS -I$includePath)
end

if ($#OBJECTS == 0) then
  echo ERROR: No object files.
  exit -1
endif


# Try to locate object files and libraries specified as linker options (in order to
# include them in the dependencies)
# step 1: separate search paths, object files, libraries and options
set LINKER_OBJECT_FILES =
set LINKER_LIBRARY_FILES =
set LINKER_SEARCH_PATHS =
set LINKER_OPTIONS = 
foreach linker_opt ($LinkerOpts)
  if (`echo $linker_opt | grep "^-L"` != "") then
    set LINKER_SEARCH_PATHS = ($LINKER_SEARCH_PATHS `echo $linker_opt | sed "s/^-L//"`)
  else if (`echo $linker_opt | grep "^-l"` != "") then
    set libraryBaseName = `echo $linker_opt | sed "s/^-l//"`
    set LINKER_LIBRARY_FILES = ($LINKER_LIBRARY_FILES $libraryBaseName)
  else if (`echo $linker_opt | grep "^-"` != "") then
    set LINKER_OPTIONS = ($LINKER_OPTIONS $linker_opt)
  else
    set LINKER_OBJECT_FILES = ($LINKER_OBJECT_FILES $linker_opt)
  endif  
end

# step 2: search for the libraries
set LINKER_FILES_ALL = `echo $LINKER_OBJECT_FILES`
foreach library ($LINKER_LIBRARY_FILES)
  set found = "0"

  foreach searchPath ($LINKER_SEARCH_PATHS)
    set sharedLib = $searchPath/lib$library.so
    set archive = $searchPath/lib$library.a
    if (-e $sharedLib) then
      set LINKER_FILES_ALL = ($LINKER_FILES_ALL $sharedLib)
      set found = "1"
    endif
    if (-e $archive) then
      set LINKER_FILES_ALL = ($LINKER_FILES_ALL $archive)
      set found = "1"
    endif
  end

  if ($found != "1") then
    echo ""
    echo "***"
    echo WARNING: Could not locate \'$library\' in any of the linker search paths. 
    echo The library \'$library\' will be omitted in the dependencies. Hence a change
    echo of this library won\'t cause a rebuild!
    echo "***"
    echo ""
  endif
end

echo ""
echo Linker search paths: 

foreach searchPath ($LINKER_SEARCH_PATHS)
  echo "    " $searchPath
end

echo ""
echo Linker options
foreach linkerOpt ($LINKER_OPTIONS)
  echo "    " $linkerOpt
end

echo ""
echo Additional libraries and object files:
foreach linkerFile ($LINKER_FILES_ALL)
  echo "    " $linkerFile
end

echo ""
echo Creating $OutputMakefile

echo \# Automatically generated makefile. Should be accepted by most make derivatives. >! $OutputMakefile
echo \# Generated: `date` >> $OutputMakefile
echo \# Better do not edit this file. >> $OutputMakefile
echo "" >> $OutputMakefile


if (`echo $OutputFile` == "") then

  echo \# No output file was given. Hence create a dummy target >> $OutputMakefile

  printf ".PHONY: DUMMY\nDUMMY : " >> $OutputMakefile

  foreach obj ($OBJECTS)
    printf "\\\n  $obj" >> $OutputMakefile
  end

  printf "\n\techo Finished. " >> $OutputMakefile
 
  printf "\n\n" >> $OutputMakefile

else if ($OutputFile:e == "a") then

  echo \# Main target \'$OutputFile\' has extension \'.a\', hence run ar. >> $OutputMakefile
  printf "$OutputFile : " >> $OutputMakefile

  foreach obj ($OBJECTS)
    printf "\\\n  $obj" >> $OutputMakefile
  end

  foreach linkerFile ($LINKER_FILES_ALL)
    printf "\\\n  $linkerFile" >> $OutputMakefile
  end

  printf "\n\t"'$(AR) -r '"$OutputFile " >> $OutputMakefile

  foreach obj ($OBJECTS)
    printf "\\\n    $obj" >> $OutputMakefile
  end
  foreach linkerFile ($LINKER_FILES_ALL)
    printf "\\\n  $linkerFile" >> $OutputMakefile
  end
  
  printf "\n\n" >> $OutputMakefile
  printf "\t"'touch '"$OutputFile\n\n" >> $OutputMakefile

else

  echo \# Main target \'$OutputFile\' is assumed to be an executable. >> $OutputMakefile
  printf "$OutputFile : " >> $OutputMakefile

  foreach obj ($OBJECTS)
    printf "\\\n  $obj" >> $OutputMakefile
  end
  foreach linkerFile ($LINKER_FILES_ALL)
    printf "\\\n  $linkerFile" >> $OutputMakefile
  end

  printf "\n\t"'$(GCC) ' >> $OutputMakefile
  printf "\\\n    -o $OutputFile" >> $OutputMakefile

  foreach obj ($OBJECTS)
    printf "\\\n    $obj" >> $OutputMakefile
  end

  foreach lnkOpt ($LinkerOpts)
    printf "\\\n    $lnkOpt" >> $OutputMakefile
  end
  
  printf "\n\n" >> $OutputMakefile
  
endif

echo "" >> $OutputMakefile
echo "clean:" >> $OutputMakefile
foreach obj ($OBJECTS)
  printf "\trm -f $obj\n" >> $OutputMakefile
end

echo "" >> $OutputMakefile
echo "ultra-clean: clean" >> $OutputMakefile
if (`echo $OutputFile` != "") then
  printf "\trm -f $OutputFile\n" >> $OutputMakefile
endif

echo "" >> $OutputMakefile
echo \# and now comes the boring part... >> $OutputMakefile
echo "" >> $OutputMakefile

foreach sourceName ($SOURCE_FILES)

  echo Processing $sourceName

#  set target=`echo $ObjectDir/$sourceName:r:t.o`
  set target=`echo $ObjectDir/$sourceName:r.o`
  set target_dir = $target:h

  printf "$target : " >> $OutputMakefile

  printf "\\\n  " >> $OutputMakefile
  gcc -x c++ $CompilerDefines -M $sourceName $INCLUDE_OPTS | sed "s/^.*://g" | sed "s/ \\ / /g" >>$OutputMakefile

  printf "\n\ttest -e $target_dir || mkdir -p $target_dir" >> $OutputMakefile
  printf "\n\t"'$(GCC)' >> $OutputMakefile
  
  foreach incOpt ($INCLUDE_OPTS)
    printf "\\\n    $incOpt" >> $OutputMakefile
  end

  foreach ccOpt ($CompilerOpts)
    printf "\\\n    $ccOpt" >> $OutputMakefile
  end

  printf "\\\n    -c -o $target" >> $OutputMakefile

  foreach src ($sourceName)
    printf "\\\n    $src" >> $OutputMakefile
  end

  printf "\n\n" >> $OutputMakefile
  
end

echo Done.
