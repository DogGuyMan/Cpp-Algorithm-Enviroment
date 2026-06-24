#!/usr/bin/env python3
"""
Custom Local Formatters용 C/C++ 포매터.
1) astyle 실행 (.astylerc 사용 → 한 줄 문장/블록 보존)
2) 연속된 여러 줄 배열 초기화 행 `{a, b, c},` 들을 세로 컬럼으로 공백 정렬

stdin 으로 파일 전체를 받아 stdout 으로 결과를 출력한다.
들여쓰기는 astyle 결과(탭) 그대로 두고, 컬럼 정렬은 공백으로만 한다.
(고정 Tab 으로는 음수/양수 폭 차이 때문에 컬럼이 깨지므로 공백을 쓴다)
"""
import sys
import os
import re
import subprocess

ASTYLE = "/opt/homebrew/bin/astyle"
ASTYLERC = ".astylerc"  # cwd(워크스페이스 루트) 기준

# <indent>{ ...inner... }<,?>  <trailing comment?>
ROW_RE = re.compile(r"^(?P<indent>\s*)\{(?P<inner>[^{}]*)\}(?P<tail>\s*,?)\s*(?P<comment>//.*|/\*.*\*/)?\s*$")


def run_astyle(text):
    try:
        p = subprocess.run(
            [ASTYLE, "--options=" + ASTYLERC],
            input=text, capture_output=True, text=True,
        )
        if p.returncode == 0 and p.stdout:
            return p.stdout
    except (FileNotFoundError, OSError):
        pass
    return text  # astyle 없으면 원본 유지


def split_top_level(inner):
    """최상위 콤마로 필드 분리 (중첩 괄호 보호)."""
    fields, depth, cur = [], 0, ""
    for ch in inner:
        if ch in "([{":
            depth += 1
            cur += ch
        elif ch in ")]}":
            depth -= 1
            cur += ch
        elif ch == "," and depth == 0:
            fields.append(cur)
            cur = ""
        else:
            cur += ch
    fields.append(cur)
    return [f.strip() for f in fields]


def align_group(group):
    """group: ROW_RE match dict 리스트. 같은 필드 수일 때만 정렬."""
    parsed = [split_top_level(m["inner"]) for m in group]
    ncols = len(parsed[0])
    if any(len(f) != ncols for f in parsed):
        return [m["raw"] for m in group]  # 필드 수 불일치 → 원본 유지
    widths = [max(len(p[c]) for p in parsed) for c in range(ncols)]

    bodies = []
    for m, fields in zip(group, parsed):
        cells = [fields[c].rjust(widths[c]) for c in range(ncols)]
        bodies.append(m["indent"] + "{" + ", ".join(cells) + "}" + m["tail"].strip())

    # trailing comment 정렬
    has_comment = any(m["comment"] for m in group)
    if has_comment:
        body_w = max(len(b) for b in bodies)
        out = []
        for b, m in zip(bodies, group):
            if m["comment"]:
                out.append(b.ljust(body_w) + "  " + m["comment"])
            else:
                out.append(b)
        return out
    return bodies


def align_arrays(text):
    lines = text.split("\n")
    out, i, n = [], 0, len(lines)
    while i < n:
        m = ROW_RE.match(lines[i])
        if m:
            group = []
            while i < n:
                mm = ROW_RE.match(lines[i])
                if not mm:
                    break
                d = mm.groupdict()
                d["raw"] = lines[i]
                group.append(d)
                i += 1
            if len(group) >= 2:
                out.extend(align_group(group))
            else:
                out.extend(g["raw"] for g in group)
        else:
            out.append(lines[i])
            i += 1
    return "\n".join(out)


def main():
    text = sys.stdin.read()
    text = run_astyle(text)
    text = align_arrays(text)
    sys.stdout.write(text)


if __name__ == "__main__":
    main()
