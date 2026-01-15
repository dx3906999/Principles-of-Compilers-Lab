#!/usr/bin/env bash

set -euo pipefail

root_dir="$(cd "$(dirname "$0")" && pwd)"
irbuilder="$root_dir/build/irbuilder"
out_dir="$root_dir/test_ir"

if [[ ! -x "$irbuilder" ]]; then
	echo "error: $irbuilder not found or not executable. Build the project first." >&2
	exit 1
fi

mkdir -p "$out_dir"

debug_flag=""
if [[ ${1-} == "-d" ]]; then
	debug_flag="-d"
fi

for c_file in "$root_dir"/tests/*.c; do
	[[ -f "$c_file" ]] || continue
	base_name="$(basename "${c_file%.c}")"
	out_file="$out_dir/$base_name.ll"
	echo "==== $(basename "$c_file") -> $(basename "$out_file") ===="
	"$irbuilder" "$c_file" $debug_flag > "$out_file"
done
