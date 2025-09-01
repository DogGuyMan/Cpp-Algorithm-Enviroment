clear
if [ $# -lt 2]; then
	echo "\$ 문제 저장소 BOJ 또는 ALGO 작성 \$2 : 식별자 작성하기"
	exit 1
fi

PSRepo="${1}"
Id="${2}"
NewDir="${PSRepo}_${Id}"
Template="$(cat "./shell/Template.txt")"

# echo $PSRepo
# echo $Id
# echo $Template

pushd "./Problems"

mkdir $NewDir
	pushd $NewDir
	mkdir "InputQuerys"
	touch main.cpp
	touch note.md
	echo "$Template" > main.cpp
	popd
popd