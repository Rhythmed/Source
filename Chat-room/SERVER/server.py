'''
    文件传输服务器 与 聊天室服务器分开
    使用不同端口号 同时工作
    文件服务器使用本地5008端口
    聊天室服务器使用本地5007端口
    

    在服务端会将接收到的信息处理后发送给所有客户端
    然后是否打印出来是在客户端进行判断
'''

import socket       # 套接字
import threading    # 线程
import queue        # 线程队列
import json         # json.dumps(some)打包   json.loads(some)解包
import os
import os.path      # 文件传输
import time         # 引入时间
import tkinter

lock = threading.Lock()     # 创建锁, 防止多个线程写入数据的顺序打乱


#    聊天室服务器类
class chatServer(object):
    def __init__(self):
        self.IP    = ''
        self.PORT  = 50007
        self.S     = ''                 # 服务器socket
        self.users = []                 # 用于存放在线用户的信息  [conn, user, addr]
        self.que   = queue.Queue()      # 用于存放客户端发送的信息的队列    [addr, data]
        
    def onSend(self):
        return
    
    # 处理客户端登录 注册 请求
    def connect(self, conn, addr):          # 处理客户端登录 注册 请求
        # 连接后将用户信息添加到users列表
        buffer   = conn.recv(1024)                # 接收用户初次连接的验证消息
        user     = buffer.decode().split()[0]     # 使用空格切片处理 获取用户名
        password = buffer.decode().split()[1]     # 获取密码
        optype   = buffer.decode().split()[2]     # 获取 请求类型 “登录 或 注册”
        
        #  响应客户端登录操作 检查用户名及密码匹配
        if optype == 'login':
            file = open(r'..\USERS_\user_list.txt','a+')    # 读取后台已注册用户信息
            file.seek(0)                        # 路径为当前目录下的 USERS_目录中的 user_list.txt 文件
            account = {}                        # 用户注册信息字典 {user, password}
            date = {}                           # 用户上次登录时间 {user, date}
            for line in file:                   # 逐行读取用户信息 
                v = line.strip().split(',')
                account[v[0]]=v[1]              # 用户名 密码 导入字典
                date[v[0]] = v[2]               # 上次登录时间 导入字典
                
        
            if (user in account):               # 用户名在字典内 且密码匹配
                if time.time() - float(date[user]) > 172800: # 距离上次登录时间大于 172800秒 即两天
                    del account[user]
                    del date[user]
                    file.seek(0)
                    file.truncate()                 # 清空文件内容 并开始重写
                    for i in account:
                        file.write(i + ',' + account[i] + ',' + date[i] + '\n')
                    
                    conn.send(b'expired')           # 回传账户过期信息
                    conn.close()
                    file.close()
                    return
                
                if password == account[user]:    # 密码 匹配成功
                    print(user, '登录成功')
                    now_time = str(time.time())     # 获取现在时间
                    date[user] = now_time           # 更新登录时间
                    file.seek(0)
                    file.truncate()                 # 清空文件内容 并开始重写
                    for i in account:
                        file.write(i + ',' + account[i] + ',' + date[i] + '\n')
                    
                    conn.send(b'success')           # 回传登录成功信息
                file.close()
                
            else:
                file.close()
                print('用户名 / 密码错误')
                conn.send(b'fail')              # 回传登录失败信息
                conn.close()                    # 并断开客户端请求连接
                return
            
        # 响应客户端注册操作 检查注册用户名是否已使用
        if optype == 'signup':
            file = open(r'..\USERS_\user_list.txt','a+')            # 读取后台已注册用户信息  [用户名,密码,日期]
            file.seek(0)
            account = {}
            date    = {}                        # 日期字典 记录上次登录时间
            for line in file:
                v = line.strip().split(',')
                account[v[0]] = v[1]
                date[v[0]] = v[2]
            
            if (user in account):               # 用户名已存在注册文件中
                print('用户名已存在')
                conn.send(b'signup_fail')       # 回传注册失败信息
                conn.close()                    # 并断开用户端连接
                return 
            else:
                print(' {name} 注册成功'.format(name = user))
                file.write(user + ',' + password + ',' + str(time.time()) + '\n')    # 在注册文件中写入注册信息
                conn.send(b'signup_success')                # 回传注册成功信息
            file.close()                                            # 关闭信息文件

 
        self.users.append((conn, user, addr))    # 将(客户端标识码 用户名 IP地址)  加入在线用户列表
        print('聊天服务器新连接:', addr, ':', user, end='')  # 打印用户名
        d = self.onlines()      # 有新连接则刷新客户端的在线用户显示  将在线用户列表返回
        self.recv(addr, d)      # 将更新后的在线用户列表 加入待发送信息队列中
        
        try:
            while True:
                data = conn.recv(1024)      # 不间断获取客户端传送的信息
                data = data.decode()
                self.recv(addr, data)       # 将收到的信息 加入信息队列
            conn.close()                    # 最后断开客户端连接
        except:
            print(user + ' 断开连接')
            self.delUsers(conn, addr)       # 将断开用户移出users
            conn.close()

    # 判断断开用户在users中是第几位并移出列表, 刷新客户端的在线用户显示
    def delUsers(self,conn, addr):
        num = 0                             # 用于判断 被移出的用户在在线用户列表的 位置
        for i in self.users:
            if i[0] == conn:                # 匹配断开连接的客户端socket
                self.users.pop(num)         # 移出在线用户列表
                print('剩余在线用户: ', end='')   # 打印剩余在线用户(conn)
                d = self.onlines()          # 更新在线用户列表
                self.recv(addr, d)          # 加入待发送队列
                print(d)
                break
            num += 1

    # 将接收到的信息(IP,端口以及发送的信息)存入que队列
    def recv(self, addr, data):
        lock.acquire()
        try:
            self.que.put((addr, data))
        finally:
            lock.release()

    # 将代发送队列中的信息 发送给已连接的用户
    def sendData(self):
        while True:
            if not self.que.empty():                # 队列非空
                message = ''                        # 服务器即将发送给客户端的信息
                data    = self.que.get()            # 取出队列第一个元素     [addr, data]
                if isinstance(data[1], str):        # 判读 已读取队列中的信息是 字符类型    (即用户发送的聊天信息)
                    for i in range(len(self.users)):# 在线用户列表信息         [conn, user, addr]
                        for j in range(len(self.users)):
                            if data[0] == self.users[j][2]:     # 待发送信息的目标addr 与 此用户addr匹配                           
                                message = ' ' + self.users[j][1] + '：' + data[1]
                                break                           # 服务器传达的消息格式为     用户名(user) : (聊天信息)
                        self.users[i][0].send(message.encode())
                message = message.split(':;')[0]
                print(message)
                
                if isinstance(data[1], list):    # 判断 已读取队列中的信息是列表类型    (即在线用户的更新)
                    data = json.dumps(data[1])   # 如果是在线用户列表  则打包后直接发送  
                    for i in range(len(self.users)):
                        self.users[i][0].send(data.encode())    # 对每个客户端广播更新 在线用户变化
            
    # 将在线用户存入online列表并返回
    def onlines(self):
        online = []
        for i in range(len(self.users)):
            online.append(self.users[i][1])     # self.users[i][i] 存放用户名
        return online



    # 运行聊天服务器
    def run(self):
        self.S = socket.socket( socket.AF_INET, socket.SOCK_STREAM ) # 生成套接字
        self.S.bind( (self.IP, self.PORT) )         # 绑定IP协议 和 端口
        self.S.listen(5)                            # 定义最大可挂起连接数 服务器开始监听工作
        print('聊天服务器正在运行...')
    
        q = threading.Thread(target=self.sendData)  # 创建线程 如果消息队列有消息 则发送出去
        q.start()                                   # 启动线程
        
        while True:                         # 不间断接收客户端连接请求
            conn, addr = self.S.accept()    # 接收客户端连接请求 并 返回 新socket和客户端IP地址及端口
            t = threading.Thread(target=self.connect, args=(conn, addr))  # 接收客户端消息
            t.start()
        
        self.S.close() 


 
# 文件服务器类
class fileServer(object):
    def __init__(self):
        self.IP   = ''
        self.PORT = 50008
        self.S    = ''
        
        self.path = r'.\RES_'       # 默认当前目录下的 RES_目录 设置为文件传输目录
        os.chdir(self.path)         # path设置为当前默认工作路径     

    # 客户端 连接 文件服务器
    def connect(self, conn, addr):
        print('文件服务器新连接: ', addr)
        
        while True:
            data = conn.recv(1024)  # 文件服务器 获取客户端文件连接请求
            data = data.decode()
            
            if data == 'quit':      # 如果连接请求显示 quit 则关闭该客户端socket
                print('Disconnected from {0}'.format(addr))
                break
            
            if len(data):
                order = data.split()[0]             # 获取客户端何种请求
                self.recv_func(order, data, conn)   # 调用recv_func方法 处理客户端请求
     
        conn.close()                # 断开用户连接       
    
    # 根据客户端请求 执行对应的处理操作
    def recv_func(self, order, data, conn):
        if order   == 'get':      
            return self.sendFile(data, conn)
        elif order == 'put':
            return self.recvFile(data, conn)
        elif order == 'dir':
            return self.sendDir(conn)
        elif order == 'cd':
            return self.cd(data, conn)

    # 传输当前目录列表
    def sendDir(self, conn):
        listdir = os.listdir(os.getcwd())
        listdir = json.dumps(listdir)
        conn.sendall(listdir.encode())

    # 传输文件操作
    def sendFile(self, message, conn):
        name = message.split()[1]  #获取第二个参数(文件名)
        fileName = r'./' + name
        with open(fileName, 'rb') as f:    
            while True:
                a = f.read(1024)
                if not a:
                    break
                conn.send(a)
        time.sleep(0.1)  # 延时确保文件发送完整
        conn.send('EOF'.encode())

    # 保存上传的文件到当前工作目录
    def recvFile(self, message, conn):
        name = message.split()[1] #获取文件名
        fileName = r'./' + name
        with open(fileName, 'wb') as file:
            while True:
                data = conn.recv(1024)
                if data == 'EOF'.encode():
                    break
                file.write(data)

    # 切换工作目录
    def cd(self, message, conn):
        message = message.split()[1]  # 截取目录名
        # 如果是新连接或者下载上传文件后的发送则 不切换 只将当前工作目录发送过去
        if message != 'same':
            f = r'./' + message
            os.chdir(f)

        path = ''
        path = os.getcwd().split('\\')  # 当前工作目录 
        for i in range(len(path)):
            if path[i] == 'RES_':
                break
        pat = ''
        for j in range(i, len(path)):
            pat = pat + path[j] + ' '
        pat = '\\'.join(pat.split())
        # 如果切换目录超出范围则退回切换前目录
        if not 'RES_' in path:
            f = r'./RES_'
            os.chdir(f)
            pat = 'RES_'
        conn.send(pat.encode())


    def run(self):
        self.S    = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
        self.S.bind( (self.IP, self.PORT) )
        self.S.listen(3)             # 文件系统服务器最大监听数
        
        print('文件服务器正在运行...')
        
        while True:
            conn, addr = self.S.accept()
            t = threading.Thread(target=self.connect, args=(conn, addr))
            t.start()
        self.S.close()

if __name__ == '__main__':
    chatSer = chatServer()
    fileSer = fileServer()
    
    chatPro = threading.Thread(target=chatSer.run)
    chatPro.start()
    filePro = threading.Thread(target=fileSer.run)
    filePro.start()

