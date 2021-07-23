import requests
import json
import socket 
import sys

def find_all(v, k):
  if type(v) == type({}):
     for k1 in v:
         if k1 == k:
            return v[k1]
         find_all(v[k1], k)

def keys_exists(element, *keys):
    '''
    Check if *keys (nested) exists in `element` (dict).
    '''
    if not isinstance(element, dict):
        raise AttributeError('keys_exists() expects dict as first argument.')
    if len(keys) == 0:
        raise AttributeError('keys_exists() expects at least two arguments, one given.')

    _element = element
    for key in keys:
        try:
            _element = _element[key]
        except KeyError:
            return False
    return True

def main():

    #app_id = '2e8b977f'
    #app_key = 'cc344dbab6efbac80aa48a5c82c093e3'

    #language = 'en'
    #word_id = 'computer'

    #url = 'https://od-api.oxforddictionaries.com/api/v2/entries/' + language + '/' + word_id.lower() 

    #r = requests.get(url, headers = {'app_id': app_id, 'app_key': app_key})

    #print(r.json()["results"][0]["lexicalEntries"][0]["entries"][0]["senses"][0]["definitions"][0])

    port, ip = 54000, "127.0.0.1"
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((ip, port))
        s.listen()
        print("start to listen")
        connection, address = s.accept()
        with connection:
            print("Connected by:", address)
            

main()