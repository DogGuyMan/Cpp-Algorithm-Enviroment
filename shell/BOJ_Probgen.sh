clear
if [ $# -lt 1 ]; then
	echo "🚸 \$1 : 백준 문제 번호 작성하기 🚸"
	exit 1
fi

ProbID="BOJ_${1#BOJ_}"   # BOJ_ 접두어 중복 방지 (1715 / BOJ_1715 둘 다 허용)
Template="$(cat "./Shell/BOJTemplate.txt")"

pushd "./Problems" > /dev/null

if [ -d "$ProbID" ]; then
	echo "❌ \"$ProbID\" : 이미 디렉토리가 있음! ❌"
	popd > /dev/null
	exit 1
fi

mkdir "$ProbID"
	pushd "$ProbID" > /dev/null
		mkdir "InputQuerys"
		touch "InputQuerys/input.txt"
		touch "output.origin.md"
		echo "$Template" > main.cpp
	popd > /dev/null
popd > /dev/null

echo "✅ \"$ProbID\" : 생성 완료 ✅"
