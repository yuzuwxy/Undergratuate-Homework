# -*- coding = utf-8 -*-
# @Time : 2022-06-07 16:27
# @Author : wxy
# @File : bookmanager.py
# @Software : PyCharm

import tkinter as tk
import tkinter.filedialog
import tkinter.messagebox
import sqlite3
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
import os

def repeated(id):
    '''
    判断是否序号重复
    :param id: Text类型序号
    :return: 重复返回True，否则返回False
    '''
    select_tb_cmd = '''
    SELECT ID FROM BOOK WHERE ID = ?
    '''
    c = conn.execute(select_tb_cmd, (id,))
    repeat = False
    for row in c:
        if row[0] == id:
            repeat = True
            break
    return repeat

def Insert(event,ID, Name, Writer, Press, Category):
    global bookinfo, booklist
    global infoWin, insertBtn

    if ID == "":
        tk.messagebox.showwarning(title = '提示', message='序号不可为空')
        return

    # 要写入的信息，从界面中输入
    info = (ID, Name, Writer, Press, Category,)
    insert_tb_cmd = '''
    INSERT INTO BOOK
    (ID, NAME, WRITER, PRESS, CATEGORY)
    VALUES (?,?,?,?,?)
    '''
    # 判断是否序号重复
    if(not repeated(ID)):
        conn.execute(insert_tb_cmd, info)
        conn.commit()
        bookinfo.append(list(info))
        tk.messagebox.showinfo(title='提示', message='添加成功')
        # booklist.insert('', 0, info)
        # 保持页面在上层
        infoWin.lift()
        # 添加完成后界面关闭，主界面恢复原来状态
        infoWin.destroy()
        mainWin.attributes('-disabled', False)
    else:
        # 弹出序号重复信息
        messBox = tk.messagebox
        messBox.showwarning(title='提示', message='序号重复')
        infoWin.lift()

def InsertInfoWin(event):
    '''
    点击添加按钮新增图书信息，弹出新的子界面用于用户填写信息，填写完毕后调用函数判断是否可以写入
    '''
    global mainWin, insertBtn
    global infoWin
    infoWin = ttk.Toplevel(mainWin)
    infoWin.title("添加书籍信息")
    # 弹出子界面时，原先的主界面用户不可再操作
    insertBtn.focus_set()
    mainWin.attributes('-disabled', True)
    # 同样使该界面位于屏幕中心且大小不可变
    newHeight = 350
    newWidth = 300
    sw = mainWin.winfo_screenwidth()
    sh = mainWin.winfo_screenheight()
    newcenterx = (sw - newWidth) / 2
    newcentery = (sh - newHeight) / 2
    infoWin.geometry('%dx%d+%d+%d' % (newWidth, newHeight, newcenterx, newcentery))
    infoWin.resizable(False, False)
    # 添加各组件
    newIDLabel = ttk.Label(infoWin, text = '序号')
    newIDLabel.grid(row = 0, column = 0, padx = 10, pady = 10)
    newIDEntry = ttk.Entry(infoWin)
    newIDEntry.grid(row = 0, column = 1, padx = 10, pady = 10, sticky = "e")
    newNemeLabel = ttk.Label(infoWin, text = '书名')
    newNemeLabel.grid(row = 1, column = 0, padx = 10, pady = 10)
    newNameEntry = ttk.Entry(infoWin)
    newNameEntry.grid(row = 1, column = 1, padx = 10, pady = 10, sticky = "e")
    newWriterLabel = ttk.Label(infoWin, text = '作者')
    newWriterLabel.grid(row = 2, column = 0, padx = 10, pady = 10)
    newWriterEntry = ttk.Entry(infoWin)
    newWriterEntry.grid(row = 2, column = 1, padx = 10, pady = 10, sticky = "e")
    newPressLabel = ttk.Label(infoWin, text = '出版社')
    newPressLabel.grid(row = 3, column = 0, padx = 10, pady = 10)
    newPressEntry = ttk.Entry(infoWin)
    newPressEntry.grid(row = 3, column = 1, padx = 10, pady = 10, sticky = "e")
    newCateLabel = ttk.Label(infoWin, text = '类别')
    newCateLabel.grid(row = 4, column = 0, padx = 10, pady = 10)
    newCateEntry = ttk.Entry(infoWin)
    newCateEntry.grid(row = 4, column = 1, padx = 10, pady = 10, sticky = "e")

    # 按钮点击后对应的事件
    okBtn = ttk.Button(infoWin, text = '确认添加')
    okBtn.grid(row = 5, column = 1, pady = 20)
    okBtn.bind('<Button-1>',lambda event : Insert(event,newIDEntry.get(), newNameEntry.get(),
                                                  newWriterEntry.get(), newPressEntry.get(), newCateEntry.get()))
    # 保持该界面在上层
    infoWin.lift()
    insertBtn.wait_window(infoWin)
    mainWin.attributes('-disabled', False)

def Search(event,patt, category, RadioBtnV, allMatchV, booklist):
    '''
    点击查询按钮后根据选择的条件对符合条件的书籍进行查找
    :param event: 鼠标点击事件
    :param patt: 输入的查询条件，可以为空，此时显示符合其他条件的所有书籍
    :param category: 选择的类别
    :param RadioBtnV: 单选框的值，输入框中字符的查找依据
    :param allMatchV: 是否全字匹配
    :param booklist: 从数据表中读入的所有书籍信息
    '''
    global bookinfo
    global mainWin
    # 清空原本的值
    for i in booklist.get_children():
        booklist.delete(i)
    recordNum = 0
    # 选择的类别为“全部”
    if category[0].get() == 1:
        for i in range(len(bookinfo)):
            idx = int(i)
            # 需要满足的其他条件：1.输入框是否为空；2.是否全字匹配
            if ((allMatchV != 1 and bookinfo[idx][RadioBtnV.get()].find(patt) != -1) or
                (allMatchV == 1 and bookinfo[idx][RadioBtnV.get()] == patt and patt != "") or
                patt == ""):
                booklist.insert('', idx, value = bookinfo[idx])
                recordNum += 1
    # 选择某些类别的书籍
    elif category[0].get() == 0:
        for i in range(len(bookinfo)):
            idx = int(i)
            yes = False
            # 是否与输入框匹配
            if not ((allMatchV != 1 and bookinfo[idx][RadioBtnV.get()].find(patt) != -1) or
                    (allMatchV == 1 and bookinfo[idx][RadioBtnV.get()] == patt) or
                    patt == ""):
                continue
            # 是否为选中的类别
            if(category[1].get() == 1 and bookinfo[idx][4] == '专业书'
                    or (category[2].get() == 1 and bookinfo[idx][4] == '报告')
                    or (category[3].get() == 1 and bookinfo[idx][4] == '小说')
                    or (category[4].get() == 1 and bookinfo[idx][4] == '工具书')
                    or (category[5].get() == 1 and (bookinfo[idx][4] != '工具书'
                                                    and bookinfo[idx][4] != '报告'
                                                    and bookinfo[idx][4] != '小说'
                                                    and bookinfo[idx][4] != '专业书'))
            ) :
                yes = True
            if(yes):
                booklist.insert('', idx, value=bookinfo[idx])
                recordNum += 1

    # 统计信息
    text = "共有 " + str(recordNum) + " 条记录"
    countLabel = ttk.Label(mainWin, text = text)
    countLabel.grid(row = 3, column = 2)

def ReadTable():
    '''
    从数据表文件中读入全部的书籍信息
    '''
    select_tb_cmd = '''
    SELECT * FROM BOOK;
    '''
    global bookinfo
    bookinfo = []
    c = conn.execute(select_tb_cmd)
    for row in c:
        bookinfo.append(list(row))

def Update(event,Event, ID, Name, Writer, Press, Category, oriItem):
    global bookinfo, UpdateorDel, mainWin, booklist

    newItem = (ID, Name, Writer, Press, Category, )
    oriItem_text = booklist.item(oriItem, 'values')
    # 如果没有修改，直接返回上一界面
    if list(newItem) == list(oriItem_text):
        UpdateorDel.destroy()
        mainWin.attributes('-disabled', False)
        return
    # 做出修改则弹出是否确认修改的提示框
    choice = tk.messagebox.askokcancel(title='提示', message='确定修改吗?', parent=UpdateorDel)
    # 不修改则退出
    if (not choice):
        UpdateorDel.destroy()
        mainWin.attributes('-disabled', False)
        return
    # 修改从数据表中读入的信息
    bookinfo.remove(list(oriItem_text))
    bookinfo.append(list(newItem))
    # 数据表中的修改：先根据序号删除书籍信息，再重新写入修改后的书籍信息
    delete_tb_cmd = '''
    DELETE FROM BOOK WHERE ID= ?;'''
    conn.execute(delete_tb_cmd, (oriItem_text[0],))
    conn.commit()
    insert_tb_cmd = '''
    INSERT INTO BOOK 
    (ID, NAME, WRITER, PRESS, CATEGORY)
    VALUES(?,?,?,?,?);
    '''
    conn.execute(insert_tb_cmd, tuple(newItem))
    conn.commit()

    # 修改表格的显示值
    row = booklist.identify_row(Event.y)
    for i in range(5):
        booklist.set(row,column = int(i), value = newItem[int(i)])
    # 退出当前界面，上一级界面返回原状态
    UpdateorDel.destroy()
    mainWin.attributes('-disabled', False)

def Delete(event, Item):
    global bookinfo, UpdateorDel, mainWin, booklist

    # 弹出确认删除的消息提示框
    choice = tk.messagebox.askokcancel(title='提示', message='确定删除该条记录吗?', parent=UpdateorDel)
    if (not choice):
        UpdateorDel.destroy()
        mainWin.attributes('-disabled', False)
        return
    # 确认删除先将读入的数据表信息删除
    Item_text = booklist.item(Item, 'values')
    try:
        bookinfo.remove(list(Item_text))
    except:
        pass
    # 再从数据表中删除该条记录
    delete_tb_cmd = '''
        DELETE FROM BOOK WHERE ID= ?;'''
    conn.execute(delete_tb_cmd, (Item_text[0],))
    conn.commit()
    booklist.delete(Item)
    # 退回上一界面，恢复原状态
    UpdateorDel.destroy()
    mainWin.attributes('-disabled', False)

def bookSelected(Event):
    '''
    双击选中表格中的书籍信息打开子窗口进行修改或删除
    :param Event: 鼠标双击事件，用于定位选中的行
    '''
    global booklist, bookinfo, mainWin, item_text

    # try用于避免双击表头响应出的错误窗口
    try:
        item = booklist.selection()[0]
        item_text = booklist.item(item, 'values')
    except:
        return

    # 弹出子窗口
    global UpdateorDel
    UpdateorDel = ttk.Toplevel(mainWin)
    UpdateorDel.title("书籍信息")
    # 禁止对上一窗口进行操作
    UpdateorDel.focus_set()
    mainWin.attributes('-disabled', True)
    # 设置在屏幕中间且大小不可变
    newHeight = 350
    newWidth = 300
    sw = mainWin.winfo_screenwidth()
    sh = mainWin.winfo_screenheight()
    newcenterx = (sw - newWidth) / 2
    newcentery = (sh - newHeight) / 2
    UpdateorDel.geometry('%dx%d+%d+%d' % (newWidth, newHeight, newcenterx, newcentery))
    UpdateorDel.resizable(False, False)

    # 子界面中的组件
    newIDLabel = ttk.Label(UpdateorDel, text='序号')
    newIDLabel.grid(row=0, column=0, padx=10, pady=10)
    newIDEntry = ttk.Entry(UpdateorDel)
    newIDEntry.insert(0,item_text[0])
    newIDEntry['state'] = 'readonly'
    newIDEntry.grid(row=0, column=1, padx=10, pady=10, sticky="e")
    newNemeLabel = ttk.Label(UpdateorDel, text='书名')
    newNemeLabel.grid(row=1, column=0, padx=10, pady=10)
    newNameEntry = ttk.Entry(UpdateorDel)
    newNameEntry.insert(0, item_text[1])
    newNameEntry.grid(row=1, column=1, padx=10, pady=10, sticky="e")
    newWriterLabel = ttk.Label(UpdateorDel, text='作者')
    newWriterLabel.grid(row=2, column=0, padx=10, pady=10)
    newWriterEntry = ttk.Entry(UpdateorDel)
    newWriterEntry.insert(0, item_text[2])
    newWriterEntry.grid(row=2, column=1, padx=10, pady=10, sticky="e")
    newPressLabel = ttk.Label(UpdateorDel, text='出版社')
    newPressLabel.grid(row=3, column=0, padx=10, pady=10)
    newPressEntry = ttk.Entry(UpdateorDel)
    newPressEntry.insert(0, item_text[3])
    newPressEntry.grid(row=3, column=1, padx=10, pady=10, sticky="e")
    newCateLabel = ttk.Label(UpdateorDel, text='类别')
    newCateLabel.grid(row=4, column=0, padx=10, pady=10)
    newCateEntry = ttk.Entry(UpdateorDel)
    newCateEntry.insert(0, item_text[4])
    newCateEntry.grid(row=4, column=1, padx=10, pady=10, sticky="e")

    # 按钮对应的点击事件
    updateBtn = ttk.Button(UpdateorDel, text = '修改')
    updateBtn.grid(row = 5, column = 1, pady = 20, sticky = "w", padx = 20)
    updateBtn.bind('<Button-1>',lambda event : Update(event, Event, newIDEntry.get(), newNameEntry.get(),
                                                  newWriterEntry.get(), newPressEntry.get(), newCateEntry.get(), item))
    delBtn = ttk.Button(UpdateorDel, text = '删除')
    delBtn.grid(row = 5, column = 1, pady = 20, sticky = "e", padx = 20)
    delBtn.bind('<Button-1>', lambda event : Delete(event, item))

    # 该界面关闭后上一界面恢复原状态
    UpdateorDel.lift()
    mainWin.attributes('-disabled', False)

def sortByColumn(col, reverse):
    '''
    双击某一列，根据该列和序号列进行排序
    :param col: 点击的列
    :param reverse: 升序或降序
    '''
    global booklist
    # 获取需要排序的列和序号列
    l = [(booklist.set(k, col), booklist.set(k, "ID"), k) for k in booklist.get_children('')]
    # 根据点击的列和序号列进行排序
    l.sort(key=lambda x:(x[0], int(x[1])), reverse=reverse)
    # 移动每一行
    for index, (val, id, k) in enumerate(l):
        booklist.move(k, '', index)

    # 重写该函数，再次点击改变升序/降序
    booklist.heading(col, command = lambda : sortByColumn(col, not reverse))

def DeleteAll(event):
    '''
    批量删除显示在当前界面的所有书籍信息
    :param event: 鼠标点击事件
    '''
    global bookinfo, booklist
    global mainWin

    # 批量删除当前表格中的所有书籍信息
    choice = tk.messagebox.askokcancel(title='提示', message='确定全部删除吗?', parent=mainWin)
    if (not choice):
        return

    # 获取当前表格中的所有书籍信息
    cnt = []
    for k in booklist.get_children(''):
        cnt.append((booklist.set(k, "ID"), booklist.set(k, "Name"), booklist.set(k, "Writer"), booklist.set(k, "Press"),
                   booklist.set(k, "Category"), ))
    delete_tb_cmd = '''
    DELETE FROM BOOK WHERE ID = ?;
    '''
    # 从数据表中删除
    for id in cnt:
        print(id)
        conn.execute(delete_tb_cmd, (id[0], ))
        conn.commit()

    for item in cnt:
        try:
            bookinfo.remove(list(item))
        except:
            pass

    # 清空界面显示的数据
    for i in booklist.get_children():
        booklist.delete(i)

def Save(event):
    '''
    将显示在界面的书籍信息以txt格式保存在指定的路径中
    :param event:鼠标点击事件
    '''
    global booklist, bookinfo, mainWin

    # 当前界面显示的所有书籍信息txt格式保存在指定路径中
    filename = tk.filedialog.askdirectory()
    filename += "/book.txt"
    # 写入文件
    try:
        file = open(filename, "w+")
        for k in booklist.get_children(''):
            file.write(booklist.set(k, "ID") + ", " + booklist.set(k, "Name")+ ", " + booklist.set(k, "Writer") + ", " +
                       booklist.set(k, "Press") + ", " + booklist.set(k, "Category"))
            file.write("\n")
    except:
        tk.messagebox.showerror(title='保存失败', message='保存失败')

def Exit():
    '''
    点击退出按钮退出或右上角叉号，点击后弹出提示框确认退出后退出
    '''
    global mainWin
    res = tk.messagebox.askokcancel("退出", "确认退出吗?")
    if(res):
        mainWin.destroy()
        exit(0)
    else:
        return

def ManagerWin(root, username):
    '''
    主界面，点击对应按钮触发事件
    :param root: 登录窗口为根窗口，主界面弹出后登陆界面隐藏
    :param username: 对用户名对应的数据表进行操作
    '''
    global mainWin,conn
    # 连接指定用户的数据库和数据表文件
    conn = sqlite3.connect(username)
    # 读入数据表文件中存储的数据信息
    ReadTable()
    mainWin = ttk.Toplevel(root)
    mainWin.title('书籍管理')
    # 设置窗口位于屏幕中间并且大小不可变
    Height = 600
    Width = 900
    sw = mainWin.winfo_screenwidth()
    sh = mainWin.winfo_screenheight()
    centerx = (sw - Width) / 2
    centery = (sh - Height) / 2
    mainWin.geometry('%dx%d+%d+%d' % (Width, Height, centerx, centery))
    mainWin.resizable(False,False)
    searchEntry = ttk.Entry(mainWin, width = 60)
    searchEntry.grid(row = 0, column = 1, padx = 10, pady = 10)
    searchBtn = ttk.Button(mainWin, text = "查询", width = 7)
    searchBtn.grid(row = 0, column = 2,  padx = 10, pady = 10)

    # 选择查找依据的单选框区域
    basisArea = ttk.Frame(mainWin)
    basisArea.grid(row = 1, column = 1, padx = 10, pady = 10)
    v = tk.IntVar()
    v.set(1)
    basedName = ttk.Radiobutton(basisArea, text = '按书名', variable = v, value = 1)
    basedName.grid(row = 0, column = 0, padx = 10)
    basedWriter = ttk.Radiobutton(basisArea, text = '按作者', variable = v, value = 2)
    basedWriter.grid(row = 0, column = 1, padx = 10)
    basedPress = ttk.Radiobutton(basisArea, text = '按出版社', variable = v, value = 3)
    basedPress.grid(row = 0, column = 2, padx = 10)
    basedCate = ttk.Radiobutton(basisArea, text = '按类别', variable = v, value = 4)
    basedCate.grid(row = 0, column = 3, padx = 10)

    # 全字匹配
    allMatchV = tk.IntVar()
    allMatchV.set(1)
    allMatch = ttk.Checkbutton(mainWin, text = '全字匹配', variable = allMatchV, onvalue = 1, offvalue = 0)
    allMatch.grid(row = 1, column = 2)

    # 选择查找指定类别的书籍
    label = ttk.Label(mainWin, text = '分类')
    checkArea = ttk.LabelFrame(mainWin, labelwidget = label)
    checkArea.grid(row = 2, column = 0, sticky = 'ew', padx = 10, pady = 10)
    allVar = tk.IntVar()
    allVar.set(1)
    categoryall = ttk.Checkbutton(checkArea, text = '全部', variable = allVar, onvalue = 1, offvalue = 0)
    categoryall.pack(anchor = 'w', padx = 10, pady = 10)
    Var1 = tk.IntVar()
    category1 = ttk.Checkbutton(checkArea, text = '专业书', variable = Var1, onvalue = 1, offvalue = 0)
    category1.pack(anchor = 'w', padx = 10, pady = 10)
    Var2 = tk.IntVar()
    category2 = ttk.Checkbutton(checkArea, text = '报告', variable = Var2, onvalue = 1, offvalue = 0)
    category2.pack(anchor = 'w', padx = 10, pady = 10)
    Var3 = tk.IntVar()
    category3 = ttk.Checkbutton(checkArea, text = '小说', variable = Var3, onvalue = 1, offvalue = 0)
    category3.pack(anchor = 'w', padx = 10, pady = 10)
    Var4 = tk.IntVar()
    category4 = ttk.Checkbutton(checkArea, text = '工具书', variable = Var4, onvalue = 1, offvalue = 0)
    category4.pack(anchor = 'w', padx = 10, pady = 10)
    Var5 = tk.IntVar()
    category5 = ttk.Checkbutton(checkArea, text = '其他', variable = Var5, onvalue = 1, offvalue = 0)
    category5.pack(anchor = 'w', padx = 10, pady = 10)
    category = (allVar, Var1, Var2, Var3, Var4, Var5)

    # 用treeview构建列表
    global booklist
    columns = ('ID','Name', 'Writer', 'Press', 'Category')
    colText = ('序号', '书名', '作者', '出版社', '类别')
    booklist = ttk.Treeview(mainWin, height = 20, columns = columns, show = 'headings')

    booklist.grid(row = 2, column = 1, columnspan = 2, padx = 10, pady = 10)
    booklist.column('ID', width=150, anchor = 'center')
    booklist.column('Name', width=150, anchor = 'center')
    booklist.column('Writer', width=150, anchor = 'center')
    booklist.column('Press', width=150, anchor = 'center')
    booklist.column('Category', width=150, anchor = 'center')
    for i in range(len(columns)):
        booklist.heading(columns[int(i)], text=colText[int(i)], command=lambda _col=columns[int(i)]: sortByColumn(_col, False))
    vbar = ttk.Scrollbar(mainWin, orient = VERTICAL, command = booklist.yview())
    booklist.configure(yscrollcommand = vbar.set)
    vbar.grid(row = 2, column = 3, sticky = "ns")

    # 按钮
    global insertBtn
    insertBtn = ttk.Button(mainWin, text = '新增书籍信息', width = 10)
    insertBtn.grid(row = 3, column = 1, sticky = 'w', padx = 10)
    deleteBtn = ttk.Button(mainWin, text = '批量删除', width = 7)
    deleteBtn.grid(row = 3, column = 1, sticky = 'w', padx = 150)
    saveBtn = ttk.Button(mainWin, text = '另存为...',)
    saveBtn.grid(row = 3, column = 1, sticky = 'w', padx = 260)
    exitBtn = ttk.Button(mainWin, text = '退出')
    exitBtn.grid(row = 3, column = 1, sticky = 'e', padx = 50)

    # 设置按钮点击事件
    insertBtn.bind('<Button-1>', InsertInfoWin)
    searchBtn.bind('<Button-1>', lambda event:Search(event,searchEntry.get(), category, v, allMatchV.get(), booklist))
    booklist.bind('<Double-Button-1>', bookSelected)
    deleteBtn.bind('<Button-1>', DeleteAll)
    saveBtn.bind('<Button-1>', Save)

    # 关闭有退出按钮和右上角的叉号，均设置提示框
    exitBtn.configure(command = Exit)
    mainWin.protocol("WM_DELETE_WINDOW", Exit)
    mainWin.lift()

    mainWin.mainloop()