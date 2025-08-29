echo "코드가 있는 디렉토리로 가서 실행시켜라."

clear
echo "코드가 있는 디렉토리로 가서 실행시켜라."

if [ $# -lt 1 ]; then
	echo "\$1 : 문제 번호 작성하기"
	exit 1
fi

curDir=$(pwd)
# echo $curDir

cd ../../../Include
includeDir=$(pwd)
# echo $(ls)

# echo '\n'
# echo "${includeDir}"

# echo '\n'
# echo "${curDir}"
cd "${curDir}"

clang++ -I "${includeDir}" \
	-fcolor-diagnostics \
	-g "${1}.cpp" \
	-o "${1}" --std=c++17

./${1}