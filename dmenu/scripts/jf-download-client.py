#!/usr/bin/env python3
import socket
from subprocess import Popen, PIPE  # nosec
import json

SERVER_HOST = "192.168.254.80"


def dmenu_command(prompt, options=[], lines=False):
    options = "\n".join(options).encode("utf8")
    res = ["dmenu", "-nb", "#222222", "-nf", "#666666", "-sb", "#000000", "-sf", "#bbbbbb", "-i", "-p", prompt]
    if lines:
        res += ["-l", str(len(options))]
    sel = Popen(res, stdin=PIPE, stdout=PIPE).communicate(input=options)[0].decode().strip()
    return sel


def show_notification(msg, level="Info"):
    dunstify_cmd = ["dunstify", "-a", "Video Archive Client", "-r", "345", level, msg]
    Popen(dunstify_cmd)


def send(s, msg):
    send_msg = msg + "|VAS_EOS"
    s.send(send_msg.encode("utf8"))
    return


def recv(s):
    data = ""
    while True:
        tmp = s.recv(1024).decode()
        if tmp == "":
            return None, None
        data += tmp
        if "|VAS_EOS" in tmp:
            break

    data = data.replace("|VAS_EOS", "")
    print(data)
    return data


def main():
    download_url = dmenu_command("Submit URL to download")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((SERVER_HOST, 7050))
    except ConnectionRefusedError:
        show_notification("Could not connect to the server.", "Error")
        return

    send(s, f"DOWNLOAD {download_url}")
    data = recv(s).split(" ")
    if data[0] == "TERMINATE":
        show_notification(" ".join(data[1:]), "Error")
        return

    send(s, "LIST DIRECTORIES")
    data = recv(s).split(" ")
    dirs = ["New"]
    dirs += json.loads(" ".join(data[1:]))["dirs"]
    dir_selection = dmenu_command("Select File Path for download", options=dirs, lines=True)

    if dir_selection == "New":
        fp = dmenu_command("Enter new File Path").strip(" ")
        ln = dmenu_command("Enter new Library Name")
        send(s, f"SELECT_NEW {fp} {ln}")
    else:
        if dir_selection not in dirs:
            show_notification("You must select 'New' or an already existing library", "Error")
            return
        send(s, f"SELECT {dir_selection}")

    data = recv(s)
    if data.split(" ")[0] == "TERMINATE":
        show_notification(" ".join(data[1:]), "Error")
        return

    send(s, "QUEUE DOWNLOAD")
    data = recv(s)
    if data == "DOWNLOAD QUEUED":
        show_notification("The URL has been queued for download.")
    else:
        show_notification("An error occured, please try again.", "Error")

    s.close()
    return


if __name__ == '__main__':
    main()
    # s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # s.connect((SERVER_HOST, 7050))
    # send(s, "LIST DOWNLOADS")
    # data = recv(s)
    # send(s, "TERMINATE CONNECTION")
    # s.close()
