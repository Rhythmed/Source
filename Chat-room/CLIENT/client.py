'''
    私聊功能
    将发送的消息从data变成data + user(自己) + chat(聊天对象)
    这里用了取巧的方法, 虽然是私聊但实际上所有客户端都能收到消息
    通过接收的消息里包含的user和chat判断是否将消息打印出来达到私聊的效果
    限制了窗口大小
'''

import socket           # 套接字
import threading        # 线程
import json             # json.dumps(some)打包   json.loads(some)解包
import tkinter          # GUI
import time
import os
import tkinter.messagebox
from tkinter.scrolledtext import ScrolledText
from tkinter import filedialog


# 全局变量
S    = ''           # socket 套接字
IP   = ''           # 服务器 IP 地址
PORT = ''           # 端口

user = ''           # 用户名
password = ''       # 密码
optype = ''         # 注册 或 登录 附加信息

userList1 = ''      # 用于显示在线用户的列表框
ii   = 0            # 用于判断是开还是关闭列表框
users = []          # 在线用户列表
chat = '---------聊天室---------'  # 聊天对象, 默认为群聊


# 注册界面类
class Register(object):
    def __init__(self):
        self.exit = False
        
        self.root = tkinter.Tk()
        self.root.title('用户注册')
        self.root.iconbitmap(".\\favicon.ico")
        self.root['height'] = 140
        self.root['width'] = 270
        self.root.resizable(0, 0)
        
        self.Account1 = tkinter.StringVar()
        self.Account1.set('')
        self.Password1 = tkinter.StringVar()
        self.Password1.set('') 
        self.Password2 = tkinter.StringVar()
        self.Password2.set('')
        
        self.labelAcc = tkinter.Label(self.root, text='用户名 :')
        self.labelAcc.place(x=20, y=10, width=80, height=20)
        self.entryAcc = tkinter.Entry(self.root, width=80, textvariable=self.Account1)
        self.entryAcc.place(x=120, y=10, width=130, height=20)

        self.labelPas = tkinter.Label(self.root, text='密码 :')
        self.labelPas.place(x=20, y=40, width=80, height=20)
        self.entryPas = tkinter.Entry(self.root, width=80, textvariable=self.Password1)
        self.entryPas.place(x=120, y=40, width=130, height=20)

        self.labelPas1 = tkinter.Label(self.root, text='密码确认 :')
        self.labelPas1.place(x=20, y=70, width=80, height=20)
        self.entryPas1 = tkinter.Entry(self.root, width=80, textvariable=self.Password2)
        self.entryPas1.place(x=120, y=70, width=130, height=20)

        self.butSignup = tkinter.Button(self.root, text='注册', command=self.onSignup)
        self.butSignup.place(x=158, y=100, width=80, height=30)
        
        self.root.bind('<Return>',self.onSignup)  # 回车绑定注册功能
        
    def onSignup(self): 
        if not self.entryAcc.get():
            tkinter.messagebox.showerror('注册失败', message='请输入 用户名')
            return
        if not self.entryPas.get():
            tkinter.messagebox.showerror('注册失败', message='请输入 密码 ')
            return
        if self.entryPas.get() != self.entryPas1.get():
            tkinter.messagebox.showerror('注册失败', message='两次输入密码不一致')
            return
        
        global S, IP, PORT
        S = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        S.connect((IP,PORT))
        
        global user, password, optype
        optype   = 'signup'                         # 表示注册的附加信息 
        user = self.entryAcc.get()
        password = self.entryPas.get()
        
        buffer = user + ' ' + password + ' ' + optype
        S.send(buffer.encode())       # 发送用户名 密码 类型 用空格分隔
        
        buffer = S.recv(1024)
        buffer = buffer.decode()
        
        if buffer == 'signup_success':
            tkinter.messagebox._show('注册成功', '已成功连接服务器')
        
        if buffer == 'signup_fail':
            tkinter.messagebox.showerror('注册失败', '当前用户名已被使用')
            S.close()
            return
        
        self.exit = True
        self.root.destroy()
    
    def run(self):
        self.root.mainloop()

# 登录界面类
class Connect(object):
    def __init__(self):
        self.connect = False           # 用于判断登录是否成功
        self.exit    = False           # 用于判断界面是否正常退出 
        
        self.root = tkinter.Tk()
        self.root.title('登录')
        self.root.iconbitmap(".\\favicon.ico")
        self.root['height'] = 140      # 高 140
        self.root['width'] = 270       # 宽 270
        self.root.resizable(0, 0)      # 窗口大小锁定
        
        self.IP1 = tkinter.StringVar()
        self.IP1.set('127.0.0.1:50007') # 默认显示的IP和端口
        self.User = tkinter.StringVar()
        self.User.set('')               # 默认用户名为空
        self.Password = tkinter.StringVar()
        self.Password.set('')
        
        # 服务器标签
        self.labelIP = tkinter.Label(self.root, text='服务器地址 :')
        self.labelIP.place(x=20, y=10, width=80, height=20)
        # IP地址及端口输入
        self.entryIP = tkinter.Entry(self.root, width=80, textvariable=self.IP1)
        self.entryIP.place(x=120, y=10, width=130, height=20)
        # 用户名标签
        self.labelUser = tkinter.Label(self.root, text='用户名 :')
        self.labelUser.place(x=20, y=40, width=80, height=20)
        # 用户名输入
        self.entryUser = tkinter.Entry(self.root, width=80, textvariable=self.User)
        self.entryUser.place(x=120, y=40, width=130, height=20)
        # 密码标签
        self.labelPassword = tkinter.Label(self.root, text='密码 :')
        self.labelPassword.place(x=20, y=70, width=80, height=20)
        # 密码输入
        self.entryPassword = tkinter.Entry(self.root, width=80, textvariable=self.Password)
        self.entryPassword.place(x=120, y=70, width=130, height=20)
        # 登录按钮
        self.butLogin = tkinter.Button(self.root,text='登录',command=self.onLogin)
        self.butLogin.place(x=32, y=100, width=80, height=30)
        # 注册按钮
        self.butSignup = tkinter.Button(self.root, text='注册', command=self.onSignup)
        self.butSignup.place(x=158, y=100, width=80, height=30)
        
        self.root.bind('<Return>',self.onLogin)  # 回车绑定登录功能
        
        
    # 点击登录按钮 执行 onLogin() 事件
    def onLogin(self,*args):                          
        if not self.entryIP.get():
            tkinter.messagebox.showerror('登录失败', message='请输入 标准的 IP地址 及 端口号')
            return
        if not self.entryUser.get():
            tkinter.messagebox.showerror('登录失败', message='请输入 用户名 ')
            return
        if not self.entryPassword.get():
            tkinter.messagebox.showerror('登陆失败', message='请输入 密码')
            return
        
        global IP, PORT, user, password, optype, S      
        user     = self.entryUser.get()
        password = self.entryPassword.get()
        optype   = 'login'                          # 表示登录的附加信息 
        IP, PORT = self.entryIP.get().split(':')    # 获取IP和端口号
        PORT = int(PORT)                            # 端口号需要为int类型
        
        if not self.connect:                        # 如果没有连接
            S = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            S.connect((IP,PORT))           # 连接服务器 
            self.connect = True
        
        buffer = user + ' ' + password + ' ' + optype
        S.send(buffer.encode())       # 发送用户名 密码 类型 用空格分隔
        
        buffer = S.recv(1024)
        buffer = buffer.decode()
        
        if buffer == 'expired':
            tkinter.messagebox.showerror('登录失败', '距离您上次登录已经超过两天 ，服务器已将您的账户删除，请重新注册')
            S.close()
            self.connect = False
            return
        
        if buffer == 'success':
            tkinter.messagebox._show('登录成功', '已成功连接服务器')
        
        if buffer == 'fail':
            tkinter.messagebox.showerror('登录失败', '请检查 用户名 或 密码 后重试')
            S.close()
            self.connect = False
            return
        

        self.root.destroy()                        # 关闭登录窗口
        self.exit = True
        
        
    # 点击注册界面按钮
    def onSignup(self,*args):
        global IP, PORT
        IP, PORT = self.entryIP.get().split(':')    # 获取IP和端口号
        PORT = int(PORT)                            # 端口号需要为int类型
        
        self.root.destroy()
        
        regis = Register()
        regis.run()
        
        if regis.exit:                  # 如果注册界面正常退出 即非点击关闭退出
            self.exit = True            # 则登录界面也正常退出
    
    # 登录界面运行
    def run(self): 
        self.root.mainloop()
         
        
# 聊天界面类
class MyClient(object):
    def __init__(self):
        self.root = tkinter.Tk()
        self.root.title(user)           # 聊天窗口用用户名命名 
        self.root.iconbitmap(".\\favicon.ico")
        self.root['height'] = 390
        self.root['width'] = 580
        self.root.resizable(0, 0)
        # 文本列表
        self.listbox = tkinter.Listbox(self.root) 
        self.listbox.place(x=5, y=0, width=570, height=322)
        # 输入文本框     
        self.entry1 = tkinter.StringVar()
        self.entry1.set('')
        entry = tkinter.Entry(self.root, width=120, textvariable=self.entry1)
        entry.place(x=5, y=348, width=499, height=40)
        
        
        # 发送按钮
        self.button = tkinter.Button(self.root, text='发送', command=self.onSend)
        self.button.place(x=513, y=353, width=60, height=30)
        self.root.bind('<Return>', self.onSend)  # 绑定回车发送信息
        # 在线用户列表
        self.userList = tkinter.Listbox(self.root)
        self.userList.place(x=445, y=0, width=130, height=322)
        # 在显示用户列表框上设置绑定事件
        self.userList.bind('<ButtonRelease-1>', self.onPrivate)  # 鼠标松开 即执行 判断
        # 显示或者关闭 在线用户列表 按钮
        self.button1 = tkinter.Button(self.root, text='在线用户', command=self.onUsers)
        self.button1.place(x=505, y=320, width=70, height=30)
        
        # 创建文件按钮
        self.fBut = tkinter.Button(self.root, text='文件', command=self.onFile)
        self.fBut.place(x=5, y=320, width=70, height=30)

    def onFile(self):
        f = fileClient(self.root)
        f.connect()


    def onSend(self,*args):
        users.append('---------聊天室---------') # 默认是群聊对象 即对所有人可见
        if chat not in users:                   # 聊天对象不在用户列表里
            tkinter.messagebox.showerror('发送失败', message='没有聊天对象!')
            return  
        if chat == user:                        # 聊天对象为自己
            tkinter.messagebox.showerror('发送失败', message='不能私聊自己!')
            return
        mes = self.entry1.get() + ':;' + user + ':;' + chat  # 添加聊天对象标记
        S.send(mes.encode())                    # 向服务器发送消息
        self.entry1.set('')                     # 发送完成后清空文本框
    def onUsers(self):
        global userList1, ii
        if ii == 1:
            self.userList.place(x=445, y=0, width=130, height=322)
            ii = 0
        else:
            self.userList.place_forget()        # 隐藏用户列表
            ii = 1
    
    # 私聊
    def onPrivate(self, *args):
        global chat
        # 获取点击的索引然后得到内容(用户名)
        indexs = self.userList.curselection()
        index = indexs[0]
        chat = self.userList.get(index)
        # 修改客户端名称
        if chat == '---------聊天室---------':    # 群聊则保持不变
            self.root.title(user)
            return    
        if chat == self.userList.get(0):
            self.root.title(user)
            return
        
        ti = '与 ' + chat + ' 的私聊'
        self.root.title(ti)
        
    # 用于时刻接收服务端发送的信息并打印,
    def recv(self):
        global users, S
        while True:
            data = S.recv(1024)
            data = data.decode()
            # 没有捕获到异常则表示接收到的是在线用户列表
            try:
                data = json.loads(data)
                users = data
                self.userList.delete(0, tkinter.END)  # 清空列表框
                number = ('     在线人数: ' + str(len(data)) + ' 人')
                self.userList.insert(tkinter.END, number)
                self.userList.itemconfig(tkinter.END,fg='green', bg="#f0f0ff")
                self.userList.insert(tkinter.END, '---------聊天室---------')
                self.userList.itemconfig(tkinter.END,fg='green')
                for i in range(len(data)):
                    self.userList.insert(tkinter.END, (data[i]))
                    self.userList.itemconfig(tkinter.END,fg='green') 
            except:
                data = data.split(':;')
                data1 = data[0]  # 消息
                data2 = data[1]  # 发送信息的用户名
                data3 = data[2]  # 聊天对象
                if data3 == '---------聊天室---------':
                    self.listbox.insert(tkinter.END, data1)  # END将信息加在最后一行
                    self.listbox.see(tkinter.END)  # 显示在最后
                    u = data1.split('：')[0]  # 截取消息中的用户名
                    if u == ' ' + user:  # 如果是自己则将则字体变为蓝色
                        self.listbox.itemconfig(tkinter.END,fg='blue')
                elif data2 == user or data3 == user:  # 显示私聊
                    self.listbox.insert(tkinter.END, data1)  # END将信息加在最后一行
                    self.listbox.see(tkinter.END)  # 显示在最后
                    self.listbox.itemconfig(tkinter.END,fg='red')
    def run(self):
        global S
        r = threading.Thread(target=self.recv)
        r.start()  # 开始线程接收信息
        self.root.mainloop()
        S.close()  # 关闭图形界面后关闭TCP连接
        


class fileClient(object):
    def __init__(self, root):
        self.S = ''             # 文件服务器socket
        
        self.root = root        # 继承聊天室界面窗口 并 重新调整窗口大小
        self.root['height'] = 390
        self.root['width']  = 760
        
        
        # 创建服务器文件列表框
        self.fileList = tkinter.Listbox(self.root)
        self.fileList.place(x=580, y=25, width=175, height=325) # 在聊天室客户端最右侧添加
        self.fileList.bind('<ButtonRelease-1>', self.run)       # 在列表框上设置绑定事件
        
        # 创建上传按钮, 并绑定上传文件功能
        self.upload = tkinter.Button(self.root, text='上传文件', command=self.put)
        self.upload.place(x=600, y=353, height=30, width=80)
        
        # 创建关闭按钮
        self.close = tkinter.Button(root, text='关闭', command=self.closeFile)
        self.close.place(x=685, y=353, height=30, width=70) 
    
    # 连接文件服务器
    def connect(self):
        global IP
        PORT2 = 50008       # 聊天室的端口为50007       文件服务器端口号为 50008
        self.S = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
        self.S.connect((IP, PORT2))
        
        self.cd('cd same')        # 初次连接文件服务器 发送获取 服务器文件目录         cd 指进入文件目录
        self.lab()
        
        self.run()

    # 创建用于绑定在列表框上的函数
    def run(self, *args):
        indexs = self.fileList.curselection()           # 当前被选中的文件 或目录
        if len(indexs):                                 # 如果文件服务器存在 目录 或文件
            index = indexs[0]
            content = self.fileList.get(index)

            if '.' in content:                              # 默认文件是带后缀名的 暂时这样处理
                content = 'get' + content
                self.get(content)
                self.cd('cd same')
            elif content == ' 返回上一级目录':
                content = 'cd ..'
                self.cd(content)
            else:
                content = 'cd ' + content
                self.cd(content)
            self.lab()  # 刷新显示页面

    # 将接收到的目录文件列表打印出来(dir), 显示在列表框中, 在pwd函数中调用
    def recvList(self, enter, lu):
        self.S.send(enter.encode())
        data = self.S.recv(4096)  
        data = json.loads(data.decode())
        self.fileList.delete(0, tkinter.END)  # 清空列表框
        lu = lu.split('\\')
        if len(lu) != 1:
            self.fileList.insert(tkinter.END, ' 返回上一级目录')
            self.fileList.itemconfig(0, fg='green')
        for i in range(len(data)):
            self.fileList.insert(tkinter.END, (' '+data[i]))
            if not '.' in data[i]:
                self.fileList.itemconfig(tkinter.END, fg='orange')
            else:
                self.fileList.itemconfig(tkinter.END, fg='blue')

    # 创建标签显示服务端工作目录
    def lab(self):
        data = self.S.recv(1024)  # 接收目录
        lu = data.decode()
        try:
            self.label.destroy()
            self.label = tkinter.Label(self.root, text=lu)
            self.label.place(x=580, y=0, )
        except:
            self.label = tkinter.Label(self.root, text=lu)
            self.label.place(x=580, y=0, )
        self.recvList('dir', lu)

    # 进入指定目录(cd)
    def cd(self, message):
        self.S.send(message.encode())

    

    # 接收下载文件(get)
    def get(self, message):
        name = message.split()
        name = name[1]  # 获取命令的第二个参数(文件名)            [操作, 文件名]
        # 选择对话框, 选择文件的保存路径
        fileName = tkinter.filedialog.asksaveasfilename(title='保存文件到', initialfile=name)
        # 如果文件名非空才进行下载
        if fileName:
            self.S.send(message.encode())
            with open(fileName, 'wb') as f:
                while True:
                    data = self.S.recv(1024)
                    if data == 'EOF'.encode():
                        tkinter.messagebox.showinfo(title='提示', message='下载成功!')
                        break
                    f.write(data)


    # 上传客户端所在文件夹中指定的文件到服务端, 在函数中获取文件名, 不用传参数
    def put(self):
        # 选择对话框
        fileName = tkinter.filedialog.askopenfilename(title='选择上传文件')
        # 如果有选择文件才继续执行
        if fileName:
            name = fileName.split('/')[-1]
            message = 'put ' + name
            self.S.send(message.encode())
            with open(fileName, 'rb') as file:
                while True:
                    a = file.read(1024)
                    if not a:
                        break
                    self.S.send(a)
                time.sleep(0.2)  # 延时确保文件发送完整
                self.S.send('EOF'.encode())
                tkinter.messagebox.showinfo(title='提示', message='上传成功!')
            self.cd('cd same')
            self.lab()  # 上传成功后刷新显示页面



    # 关闭文件管理器, 待完善
    def closeFile(self):
        self.root['height'] = 390
        self.root['width'] = 580
        # 关闭连接
        self.S.send('quit'.encode())
        self.S.close()


    


     
        
if __name__ == '__main__':
    c = Connect()
    c.run()
    
    if c.exit:
        client = MyClient()
        client.run()
    
    
    
    
    
    
    
    
