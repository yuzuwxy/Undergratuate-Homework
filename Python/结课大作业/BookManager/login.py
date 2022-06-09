# -*- coding = utf-8 -*-
# @Time : 2022-06-07 15:50
# @Author : wxy
# @File : login.py
# @Software : PyCharm

import tkinter as tk
import ttkbootstrap as ttk
import tkinter.messagebox
import sqlite3

import bookmanager
# 连接用户信息数据库
connuser = sqlite3.connect("BookManager")


def createTable(name):
    '''
    建立登录用户对应的数据库和数据表文件
    :param name: 用户名
    '''
    create_tb_cmd = '''
        CREATE TABLE IF NOT EXISTS BOOK
        (ID TEXT NOT NULL,
        NAME TEXT NOT NULL,
        WRITER TEXT NOT NULL,
        PRESS TEXT NOT NULL,
        CATEGORY TEXT NOT NULL);
        '''
    connbook = sqlite3.connect(name)
    connbook.execute(create_tb_cmd)
    connbook.commit()


def Login():
    '''
    完成登录界面
    :return:
    '''
    def login_click():
        '''
        点击登录，查询密码是否正确，登陆后进入管理系统主界面
        '''
        global conn
        # 获取用户名和密码
        username = usernameEntry.get()
        password = passwordEntry.get()
        # 连接该用户对应的数据库
        conn = sqlite3.connect(username)
        # 判断用户名和密码是否正确，弹出消息框提示
        select_tb_cmd = '''
        SELECT USERNAME, PASSWORD from USER;
        '''
        curcor = connuser.execute(select_tb_cmd)
        haveUser = False
        for row in curcor:
            # 存在该用户，判断密码是否正确
            if(row[0] == username):
                haveUser = True
                messbox = tk.messagebox
                # 密码错误弹出消息提示框
                if(row[1] != password):
                    messbox.showerror(title = '提示', message = '密码错误')
                # 密码正确，连接或创建对应的数据库或数据表文件
                # 登录成功隐藏登录窗口，进入书籍管理主界面
                elif(row[1] == password):
                    loginWin.withdraw()
                    createTable(username)
                    bookmanager.ManagerWin(loginWin, username)
        # 没有该用户则弹出提示，用户可进行注册
        if(not haveUser):
            tk.messagebox.showwarning(title='提示', message='没有该用户')

    def register_click():
        '''
        点击注册，判断用户是否已经存在，弹出提示；注册成功也弹出提示信息
        '''
        username = usernameEntry.get()
        password = passwordEntry.get()
        user = (username, password,)
        select_tb_cmd = '''
                SELECT USERNAME, PASSWORD from USER;
                '''
        curcor = connuser.execute(select_tb_cmd)
        haveUser = False
        # 规定用户不能同名，用户名已注册时弹出提示
        for row in curcor:
            if (row[0] == username):
                haveUser = True
                tk.messagebox.showwarning(title='提示', message='用户已存在')
        # 新用户则讲用户名和密码写入数据表文件中
        if (not haveUser):
            insert_tb_cmd = '''
            INSERT INTO USER (USERNAME, PASSWORD) VALUES (?, ?);
            '''
            connuser.execute(insert_tb_cmd, user)
            connuser.commit()
            # 弹出注册成功的提示框，注册成功后可登录
            tk.messagebox.showinfo(title='提示', message='注册成功')


    loginWin = ttk.Window(themename='pulse')
    loginWin.title("登录")
    # 设置窗口在屏幕中心且大小不可变
    Height = 160;Width = 350
    sw = loginWin.winfo_screenwidth();sh = loginWin.winfo_screenheight()
    centerx = (sw - Width) /2
    centery = (sh - Height) / 2
    loginWin.geometry('%dx%d+%d+%d' % (Width, Height, centerx, centery))
    loginWin.resizable(False, False)
    # 在界面添加各组件
    usernameLabel = ttk.Label(loginWin, text='用户名').grid(row=0, column=1)
    # 默认admin账户登录
    Var = tk.StringVar(value = "admin")
    usernameEntry = tk.Entry(loginWin, font=("微软雅黑", 10), textvariable = Var)
    usernameEntry.grid(row=0, column=2, padx = 10, pady = 10)
    passwordLabel = ttk.Label(loginWin, text='密  码').grid(row=1, column=1)
    Var = tk.StringVar(value = "123456")
    passwordEntry = tk.Entry(loginWin, font=("微软雅黑", 10), textvariable = Var, show="*")
    passwordEntry.grid(row=1, column=2, padx = 10, pady = 10)
    loginWin.grid_columnconfigure(1, minsize=100)
    loginBtn = ttk.Button(loginWin, text="登录", width=7)
    loginBtn.grid(row=2, column=2, sticky="w", padx = 10, pady = 10)
    registerBtn = ttk.Button(loginWin, text="注册", width=7)
    registerBtn.grid(row=2, column=2, sticky="e", padx = 10, pady = 10)

    # 添加按钮点击事件
    registerBtn.config(command = register_click)
    loginBtn.config(command = login_click)

    loginWin.mainloop()
