import requests
import os

ret = requests.get("https://random-word-api.herokuapp.com/word?number=1")
if ret.status_code == 200:
	fd = open("pass.txt", "w")
	fd.write(ret.text.split('"')[1])
	fd.close()

os.system("./hangman")