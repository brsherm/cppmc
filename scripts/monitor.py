import subprocess

subprocess.run(['''tail''', '-F', 'a.txt' | sed "s/\${\([0-9]*\)}/`echo '\u001b[38;5;\1m'`/; s/$/`echo '\u001b[39m'`/g"'''])