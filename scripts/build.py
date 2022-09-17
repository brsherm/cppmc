# 90 lines of jank

from hashlib import blake2b
import subprocess
import os

packages = ['glew', 'glfw3']
target = 'mc'

dependencies = dict()

def recursive_file_locator(dir_name, extension) -> list[str]:
  files_list = []
  with os.scandir(dir_name) as it:
    for entry in it:
      if entry.name.startswith('.'): continue
      if entry.is_file() and entry.name.endswith(extension):
        filename = f'{dir_name}/{entry.name}'
        files_list.append(filename)
        if filename not in dependencies:
          dependencies[filename] = []
          with open(filename) as f:
            line = f.readline()
            while line:
              if line.find("#include") != -1 and line.find('"') != -1:
                dependencies[filename].append((dir_name, line.split('"')[1]))
              line = f.readline()
      elif entry.is_dir():
        files_list.extend(recursive_file_locator(f'{dir_name}/{entry.name}', extension))
  return files_list

def find_source_files():
  return recursive_file_locator('src', '.cpp')

def find_header_files():
  return recursive_file_locator('src', '.h')

header_files = find_header_files()
source_files = find_source_files()

def find_object_files():
  return [f.replace('.cpp', '.o').rpartition('/')[2].rstrip('.o')+'-'+blake2b(f.encode(), digest_size=4).hexdigest()[0:7]+'.o' for f in source_files]

object_files = find_object_files()

def inc_dir():
  return f'-I../src -I.. $(shell pkg-config --cflags {" ".join(packages)})'

# create makefile
try: os.mkdir('bin')
except: pass

f = open('bin/makefile', 'w')

f.write(f'''OBJS = {' '.join(object_files)}
INC_DIR = {inc_dir()}
LDFLAGS=$(shell pkg-config --libs glew glfw3) -framework OpenGL
{target}: $(OBJS)
\tg++ $(OBJS) $(INC_DIR) $(LDFLAGS) -o {target} -std=c++11
''')

real_dependencies = {}

for file in dependencies:
  real_dependencies[file] = []
  for dir_name, file_name in dependencies[file]:
    if file_name.find("/") == -1:
      real_dependencies[file].append(f'{dir_name}/{file_name}')
    else:
      k = os.path.join(dir_name, file_name)
      if os.path.exists(k):
        real_dependencies[file].append(k)
      else:
        real_dependencies[file].append(file_name)

for sf, of in zip(source_files, object_files):
  header = sf.replace('.cpp', '.h')
  f.write(f'''
{of}: ../{sf} {" ".join([f'../{d}' for d in real_dependencies[sf]])}
\tg++ ../{sf} -c $(INC_DIR) -o {of} -std=c++11
  ''')

f.close()

# run it
os.chdir('./bin')
subprocess.run(args = ['make'])

# remove it
# os.remove('makefile')