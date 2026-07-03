clear
if [ $# -lt 2 ]; then
    echo "\$1 : 삼성 문제 ID 작성하기, \$2 : 쿼리모드 (0 : 비 활성화)"
    exit 1
fi

ProbID="SWEA_${1#SWEA_}"   # SWEA_ 접두어 중복 방지 (1231 / SWEA_1231 둘 다 허용)
ProbDir="./Problems/${ProbID}"

if [ ! -f "${ProbDir}/main.cpp" ]; then
    echo "존재하지 않는 문제입니다: ${ProbDir}/main.cpp"
    exit 1
fi

echo "_________${ProbID} Build!_________"

clang++  -I"./Include" \
    -g -fno-omit-frame-pointer \
    -fcolor-diagnostics -fno-common -fsanitize=undefined,integer -fno-sanitize-recover=all \
	-Wall -Wextra -Werror -Warray-bounds -Wshadow -Wduplicate-decl-specifier -Wredundant-decls \
    -Wno-error=unused-but-set-variable -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -Wno-implicit-function-declaration \
	--std=c++17 -O1 -g "${ProbDir}/main.cpp" -o "${ProbDir}/main"

if [ $? -ne 0 ]; then
    echo "_________${ProbID} Build Failed!_________"
    exit 1
fi

QueryMode="$2"
InputQueryDir="${ProbDir}/InputQuerys"
LogFile="${ProbDir}/log.txt"
QueryFiles=""

: > "${LogFile}"   # 로그 초기화

if [ $QueryMode -ne 0 ]; then
    echo "_________${ProbID} Execute With Query!_________\n"
    QueryFiles=$(ls ${InputQueryDir});
    for file in ${QueryFiles}; do
        echo "$file Start \n"
        echo "===== ${file} =====" >> "${LogFile}"
        # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main
        ./Problems/${ProbID}/main "./Problems/${ProbID}/InputQuerys/${file}" "" >> "${LogFile}"
        echo "End \n"
    done
else
    echo "_________${ProbID} Execute Normal!_________\n"
    # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main
    ./Problems/${ProbID}/main > "${LogFile}"
fi

echo "_________${ProbID} Log -> ${LogFile}_________"
echo "_________${ProbID} Finished!_________"