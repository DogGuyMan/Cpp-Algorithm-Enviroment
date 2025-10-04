clear
if [ $# -l 2 ]; then
    echo "\$1 : 알고스팟 문제 ID 작성하기, \$2 : 쿼리모드 (0 : 비 활성화)"
    exit 1
fi

ProbID="ALGO_$1"

echo "_________${ProbID} Build!_________"

clang++  -I"./Include" \
    -g -fno-omit-frame-pointer \
    -fcolor-diagnostics -fno-common -fsanitize=undefined,integer -fno-sanitize-recover=all \
	-Wall -Wextra -Werror -Warray-bounds -Wshadow -Wduplicate-decl-specifier -Wredundant-decls \
    -Wno-error=unused-but-set-variable -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -Wno-implicit-function-declaration \
	--std=c++17 -O1 -g "./Problems/${ProbNum}/main.cpp" -o "./Problems/${ProbNum}/main"

QueryMode="$2"
InputQueryDir="./Problems/${ProbID}/InputQuerys"
QueryFiles=""

if [ $QueryMode -ne 0 ]; then 
    echo "_________${ProbID} Execute With Query!_________\n"
    QueryFiles=$(ls ${InputQueryDir});
    for file in ${QueryFiles}; do
        echo "$file Start \n"
        # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main
        ./Problems/${ProbID}/main "./Problems/${ProbID}/InputQuerys/${file}" ""
        echo "End \n"
    done
else
    echo "_________${ProbID} Execute Normal!_________\n"
    # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main
    ./Problems/${ProbID}/main
fi

echo "_________${ProbID} Finished!_________"