from hashlib import blake2b
import subprocess
import os

packages = ['glew', 'glfw3']
target = 'mc'

def recursive_file_locator(dir_name, extension) -> list[str]:
  files_list = []
  with os.scandir(dir_name) as it:
    for entry in it:
      if entry.name.startswith('.'): continue
      if entry.is_file() and entry.name.endswith(extension):
        files_list.append(f'{dir_name}/{entry.name}')
      elif entry.is_dir():
        files_list.extend(recursive_file_locator(f'{dir_name}/{entry.name}', extension))
  return files_list

def source_files():
  return recursive_file_locator('src', '.cpp')

def header_files():
  return recursive_file_locator('src', '.h')

def object_files():
  return [f.replace('.cpp', '.o').rpartition('/')[2].rstrip('.o')+'-'+blake2b(f.encode(), digest_size=3).hexdigest()+'.o' for f in source_files()]

def inc_dir():
  return f'-I../src $(shell pkg-config --cflags {" ".join(packages)})'

# create makefile
try: os.mkdir('bin')
except: pass

f = open('bin/makefile', 'w')

f.write(f'''OBJS = {' '.join(object_files())}
INC_DIR = {inc_dir()}
LDFLAGS=$(shell pkg-config --libs glew glfw3) -framework OpenGL
{target}: $(OBJS)
\tg++ $(OBJS) $(INC_DIR) $(LDFLAGS) -o {target}
''')

sfof = zip(source_files(), object_files())
for sf, of in sfof:
  header = sf.replace('.cpp', '.h')
  f.write(f'''
{of}: ../{sf} {f'../{header}' if header in header_files() else ''} ../src/shared/config/config.hpp
\tg++ ../{sf} -c $(INC_DIR) -o {of}
  ''')

f.close()

# run it
os.chdir('./bin')
subprocess.run(args = ['make'])

# remove it
os.remove('makefile')