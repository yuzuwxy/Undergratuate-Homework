# -*- coding = utf-8 -*-
# @Time : 2022-06-07 12:06
# @Author : wxy
# @File : MainLoop.py
# @Software : PyCharm

import sqlite3

import login

# 连接存储用户信息的数据表
connuser = sqlite3.connect("BookManager")

def createTable():
    '''
    创建数据表，分别存储用户信息和图书信息
    '''
    global connuser
    try:
        create_tb_cmd = '''
        CREATE TABLE IF NOT EXISTS USER
        (USERNAME TEXT,
        PASSWORD TEXT);
        '''
        connuser.execute(create_tb_cmd)
    except:
        print("Create table failed")

    ## admin为默认用户
    cursor = connuser.execute("SELECT USERNAME, PASSWORD FROM USER WHERE USERNAME='admin'")
    haveAdmin = False
    for row in cursor:
        if(row[0] == 'admin') : haveAdmin = True
    if(not haveAdmin):
        connuser.execute("INSERT INTO USER (USERNAME, PASSWORD) VALUES ('admin', '123456');")
        connuser.commit()

if __name__ == "__main__":
    createTable()
    # 进入登录界面
    login.Login()