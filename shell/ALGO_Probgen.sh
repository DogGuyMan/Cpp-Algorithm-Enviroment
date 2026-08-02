clear
if [ $# -lt 1 ]; then
	echo "🚸 \$1 : 알고스팟 문제 ID 작성하기 🚸"
	exit 1
fi

Id="${1#ALGO_}"
Id="${Id#BOJ_}"
ProbID="ALGO_${Id}"

if [ -d "./Problems/${ProbID}" ]; then
	echo "❌ \"$ProbID\" : 이미 디렉토리가 있음! ❌"
	exit 1
fi

# ALGO는 BOJ와 동일한 템플릿/구조를 쓰므로 BOJ_Probgen으로 생성 후 이름만 바꿔치기
bash "./Shell/BOJ_Probgen.sh" "$Id" || exit 1

mv "./Problems/BOJ_${Id}" "./Problems/${ProbID}"

echo "✅ \"$ProbID\" : 생성 완료 ✅"
