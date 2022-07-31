import os

try:
  with os.scandir('bin') as it:
    for entry in it:
      os.remove('bin/' + entry.name)
  os.rmdir('bin')
except FileNotFoundError: pass