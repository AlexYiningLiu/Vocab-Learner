import requests
import json
import socket 
import sys

def requestDef(word_id):
    #print(word_id)
    app_id = '2e8b977f'
    app_key = 'cc344dbab6efbac80aa48a5c82c093e3'
    language = 'en'
    url = 'https://od-api.oxforddictionaries.com/api/v2/entries/' + language + '/' + word_id.lower() 
    r = requests.get(url, headers = {'app_id': app_id, 'app_key': app_key})
    try:
        oxford_def = r.json()["results"][0]["lexicalEntries"][0]["entries"][0]["senses"][0]["definitions"][0]
    except:
        print("No definition returned from Oxford")
        return "None"
    #print(oxford_def)
    return oxford_def

def main():
    app_id = '2e8b977f'
    app_key = 'cc344dbab6efbac80aa48a5c82c093e3'
    language = 'en'


    port, ip = 54000, "127.0.0.1"
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((ip, port))
        s.listen()
        print("start to listen")
        connection, address = s.accept()
        with connection:
            print("Connected by:", address)
            while True:
                query = connection.recv(4096)
                if not query:
                    print("invalid")
                    break
                word_id = query.decode('utf-8')
                word_id = word_id[:len(word_id)-1]
                oxford_def = requestDef(word_id)                
                connection.sendall(str.encode(oxford_def))
main()