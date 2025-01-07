if [ $# -l 2 ]; then
    echo "\$1 : 백준 문제 번호 작성하기, \$2 : 쿼리모드 (0 : 비 활성화)"
    exit 1
fi

ProbNum="BOJ_$1"

# MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbNum}/main

echo "_________${ProbNum} Build!_________"

clang++ -fcolor-diagnostics -g "./Problems/${ProbNum}/main.cpp" -o "./Problems/${ProbNum}/main" --std=c++17


QueryMode="$2"
InputQueryDir="./Problems/${ProbNum}/InputQuerys"
QueryFiles=""

if [ $QueryMode -ne 0 ]; then 
    echo "_________${ProbNum} Execute With Query!_________\n"
    QueryFiles=$(ls ${InputQueryDir});
    for file in ${QueryFiles}; do
        echo "$file Start \n"
        ./Problems/${ProbNum}/main "./Problems/${ProbNum}/InputQuerys/${file}" ""
        echo "End \n"
    done
else
    echo "_________${ProbNum} Execute Normal!_________\n"
    ./Problems/${ProbNum}/main
fi

echo "_________${ProbNum} Finished!_________"