clear
if [ $# -l 2 ]; then
    echo "\$1 : 삼성 문제 ID 작성하기, \$2 : 쿼리모드 (0 : 비 활성화)"
    exit 1
fi

ProbID="SWEA_$1"

# MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main

echo "_________${ProbID} Build!_________"

clang++ -I"./Include" \
	-fcolor-diagnostics \
	-fno-common \
	-Wall -Wextra \
	-Wshadow \
	-Wduplicate-decl-specifier \
	-Wredundant-decls \
	-g "./Problems/${ProbID}/main.cpp" -o "./Problems/${ProbID}/main" --std=c++17

QueryMode="$2"
InputQueryDir="./Problems/${ProbID}/InputQuerys"
QueryFiles=""

if [ $QueryMode -ne 0 ]; then 
    echo "_________${ProbID} Execute With Query!_________\n"
    QueryFiles=$(ls ${InputQueryDir});
    for file in ${QueryFiles}; do
        echo "$file Start \n"
        # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main "./Problems/${ProbID}/InputQuerys/${file}" ""
        ./Problems/${ProbID}/main "./Problems/${ProbID}/InputQuerys/${file}" ""
        echo "End \n"
    done
else
    echo "_________${ProbID} Execute Normal!_________\n"
    # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main
    ./Problems/${ProbID}/main
fi

echo "_________${ProbID} Finished!_________"