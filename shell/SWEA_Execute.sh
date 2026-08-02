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
    -fno-sanitize=unsigned-integer-overflow,unsigned-shift-base \
    -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG \
	-Wall -Wextra -Werror -Warray-bounds -Wshadow -Wduplicate-decl-specifier -Wredundant-decls \
    -Wno-error=unused-but-set-variable -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -Wno-implicit-function-declaration -Wno-error=sign-compare \
	--std=c++17 -O1 -g "${ProbDir}/main.cpp" -o "${ProbDir}/main"

if [ $? -ne 0 ]; then
    echo "_________${ProbID} Build Failed!_________"
    exit 1
fi

QueryMode="$2"
InputQueryDir="${ProbDir}/InputQuerys"
LogFile="${ProbDir}/log.txt"
QueryFiles=""
TimeoutSec=1   # 무한루프 방지: 이 시간(초) 넘으면 강제 종료

if ! command -v timeout >/dev/null 2>&1; then
    echo "timeout 명령을 찾을 수 없습니다. 'brew install coreutils'로 설치하세요."
    exit 1
fi

: > "${LogFile}"   # 로그 초기화

if [ $QueryMode -ne 0 ]; then
    echo "_________${ProbID} Execute With Query!_________\n"
    QueryFiles=$(ls ${InputQueryDir});
    for file in ${QueryFiles}; do
        echo "$file Start \n"
        echo "===== ${file} ====="
        # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main "./Problems/${ProbID}/InputQuerys/${file}" "" >> "${LogFile}"
        timeout -k 1 "${TimeoutSec}" ./Problems/${ProbID}/main "./Problems/${ProbID}/InputQuerys/${file}" "" >> "${LogFile}"
        if [ $? -eq 124 ]; then
            echo "⚠️  ${file}: ${TimeoutSec}초 초과로 강제 종료됨 (무한루프 의심)"
        fi
        echo "End \n"
    done
else
    echo "_________${ProbID} Execute Normal!_________\n"
    # MallocStackLogging=1 leaks --atExit --list -- ./Problems/${ProbID}/main > "${LogFile}"
    timeout -k 1 "${TimeoutSec}" ./Problems/${ProbID}/main > "${LogFile}"
    if [ $? -eq 124 ]; then
        echo "⚠️  ${ProbID}: ${TimeoutSec}초 초과로 강제 종료됨 (무한루프 의심)"
    fi
fi

echo "_________${ProbID} Log -> ${LogFile}_________"
echo "_________${ProbID} Finished!_________"