# usage

if [ $# -lt 1 ]; then
    echo "Build and run nasm file."
    echo "Usage: $0 <target.asm>"
    exit 1
fi

# parse flags.
# t - build target
# i - input that will be entered to stdin while program runtime.
while getopts i:t: flag
do
    case "${flag}" in
        i) input=${OPTARG};;
        t) target=${OPTARG};;
    esac
done
target="${target%.*}"

# building
echo -n "Building ${target}.asm.. "
nasm -f elf32 "${target}.asm" -o "${target}.o"
echo "Done."

# linking
echo -n "Building ${target} with C macros.. "
gcc -no-pie -w "${target}.o" macro.c -o "${target}"
echo "Done."

# clean
echo -n "Clean unnesessary .o file.. "
rm -f "${target}.o"
echo "Done."

# remove ./ if exists from beginning of
target=$(echo "${target}" | sed 's/^\.\///')
echo "Build is finished."
if [ "${input}" != "" ] 
then
    echo "\"${input}\" will be pre-entered to stdin."
    echo
    echo "${input}" | "${target}"
else
    "${target}"
fi
echo
echo "Finishing..."
