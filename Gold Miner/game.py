# coding=gbk

import  sys
import  time
import  random
import  pygame
from    pygame.locals import *


#    print_text function    *********************************
#
def print_text(font,x,y,text,color=(255,255,255)):            #    print text into screen
    imgText = font.render(text,True,color)
    screen.blit(imgText,(x,y))
      
def game_help():                                              #    Game help description
    print_text(font,70,30,"黄金矿工游戏")
    print_text(font,20,80,"操作按键A 控制矿工向左移动")
    print_text(font,20,110,"操作按键D 控制矿工向右移动")
    print_text(font,20,140,"在合适位置 单击鼠标左键 向下挖取矿石")
    print_text(font,20,170,"游戏随机在地下位置生成矿石 有大 中 小黄金")
    print_text(font,20,200,"也会随机产生钻石 以及石头")
    print_text(font,20,230,"挖出各类矿石的难度不同 所获得的分数也不同")
    print_text(font,20,260,"其中大 中 小黄金 分别为 5 10 20分")
    print_text(font,20,290,"挖出钻石 得50分 挖出石头扣10分")
    print_text(font,20,320,"您可以在开始界面 选择游戏难度")
    print_text(font,20,350,"并且需要在120秒时间内 达到指定的通关分数")
    print_text(font,20,380,"否则游戏失败")
    print_text(font,400,410,"按下空格键继续")
    
    
    
    



#    class                ***********************************
#

#    ********************************************************

class Gold():                                       #    class gold
    def __init__(self):
        self.exit   = True                          #    whether draw the gold
        self.select = False                         #    whether had been selected
        self._size  = random.randint(0,2)           #    Randomly determine the size
        if self._size == 0:                         #    0 small 1 media 2 large
            self._y = random.randint(30,height/2) + 100    
            self._x = random.randint(30,width-30)
            self.score = 5
            self._vy   = 0.4
        if self._size == 1:
            self._y = random.randint(150,height/2) + 100       #    
            self._x = random.randint(30,width-30)
            self.score = 10
            self._vy   = 0.1
        if self._size == 2:
            self._y = random.randint(height/2+50,height - 60)       #    
            self._x = random.randint(30,width-30)
            self.score = 20
            self._vy   = 0.08                       #    

    def draw(self):                                 #    draw the gold
        if self._size == 0:
            if self.exit:
                pygame.draw.rect(screen,yellow,(self._x-10,self._y,20,20))
                pygame.draw.rect(screen,black,(self._x-10,self._y,20,20),3)
        if self._size == 1:
            if self.exit:
                pygame.draw.rect(screen,yellow,(self._x-20,self._y,40,40))
                pygame.draw.rect(screen,black,(self._x-20,self._y,40,40),3)
        if self._size == 2:
            if self.exit:
                pygame.draw.rect(screen,yellow,(self._x-30,self._y,60,60))
                pygame.draw.rect(screen,black,(self._x-30,self._y,60,60),3)
                
    def get(self,x,y):                              #    Determine if it is selected
        if self.exit:
            if self._x-10 >= x and i._x <= x + 60:
                if self._y == y:
                    self.select = True           

class Stone():                                      #    class gold
    def __init__(self):
        self.exit = True
        self.select = False
        self._y = random.randint(height/2,height - 60)
        self._x = random.randint(30,width-30)
        self.score = -10
        self._vy   = 0.1

    def draw(self):
        if self.exit:
            pygame.draw.rect(screen,(65,90,70),(self._x-22,self._y,45,45))
            pygame.draw.rect(screen,black,(self._x-22,self._y,45,45),3)
                
    def get(self,x,y):
        if self.exit:
            if self._x >= x and self._x <= x + 60:
                if self._y == y:
                    self.select = True 
                    
class Diamond():                                      #    class gold
    def __init__(self):
        self.exit = True
        self.select = False
        self._y = random.randint(height/2,height - 60)
        self._x = random.randint(30,width-30)
        self.score = 50
        self._vy   = 0.5

    def draw(self):
        if self.exit:
            pygame.draw.rect(screen,(153,255,255),(self._x-8,self._y,16,16))
            pygame.draw.rect(screen,black,(self._x-8,self._y,16,16),3)
                
    def get(self,x,y):
        if self.exit:
            if self._x >= x and self._x <= x + 60:
                if self._y == y:
                    self.select = True 
     
class Miner(object):                                #    class miner
    def __init__(self):
        self._x = width/2
        self._y = 100
        self._vy = 0.5
        self.up     = False                         #    turn down or up
        self.down   = False
        self.left  = False                          #    turn left or right
        self.right = True
        self.imgR = pygame.image.load("0.png").convert_alpha()
        self.imgL = pygame.image.load("1.png").convert_alpha()
        self.img  = pygame.image.load("2.png").convert_alpha()  #    tool image
    def draw(self):
        if self.left:
            screen.blit(self.imgL,(self._x,20))
        else:
            screen.blit(self.imgR,(self._x,20))
        pygame.draw.rect(screen,black,(self._x+25,100,5,self._y - 100))     #  draw hook
        screen.blit(self.img,(self._x,self._y))
            
#    ********************************************************






#    global variable    *************************************
#
main_interface       = True             #    Determine whether to load main frame
grade_interface      = False            #    select which grade
help_interface       = False            #    Determine whether to load help frame
game_interface       = False            #    Determine whether to load game frame
result_interface     = False            #    Determine whether to load final frame
game_over            = False            #    loop
width                = 800              #    screen width
height               = 600              #    screen height

yellow               = (255,255,55)     #    yellow
black                = (0,0,0)          #    black
red                  = (255,0,0)        #    red
blue                 = (0,0,100)        #    blue
mouse_x = mouse_y    = 0
click                = False            #    mouse click status
clock_start          = 0.0              #    save the time of game_start
Total_time           = 120.0            #    time

score  = 0
target = 400

#    ********************************************************


#    pygame initialization    *******************************
pygame.init()                                       #    pygame initialization
screen = pygame.display.set_mode((width,height))         #    set the size of game_frame
pygame.display.set_caption("GoldNuggets")           #    set the caption of GoldNuggets
screen.fill((0,0,100))

font = pygame.font.SysFont("SimHei",28)
font1 = pygame.font.SysFont("SimHei",56)


golds = [Diamond(),Diamond(),Diamond(),Diamond(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Gold(),Stone(),Stone(),Stone(),Stone(),Stone()]

player = Miner()


while not game_over:                                         #    game loop
    if main_interface:                              #    response main_interface 
        for event in pygame.event.get():            #    get game event messages
            if event.type == QUIT:                  #    click close
                sys.exit()                          #    exit game
            elif event.type == MOUSEMOTION:
                mouse_x,mouse_y = event.pos         #    get the position of mouse
            elif event.type == MOUSEBUTTONDOWN:
                click = True                        #    save the mouse click status
        keys = pygame.key.get_pressed()             #    get the key_pressed message
        if keys[K_ESCAPE]:                          #    pressed ESC key
            sys.exit()                              #    exit
            
        screen.fill(blue)                      #    fill screen use color
        
        print_text(font1,width/2-110,100,"黄金矿工")
        pygame.draw.rect(screen,yellow,(width/2-90,260,180,30))
        pygame.draw.rect(screen,yellow,(width/2-90,320,180,30))
        if(mouse_x > width/2-85 and mouse_x < width/2+85):
            if(mouse_y > 265 and mouse_y < 285):
                print_text(font,width/2-55,261,"开始游戏",red)
                print_text(font,width/2-55,321,"游戏帮助",black)
                if click:
                    main_interface = False
                    grade_interface = True

            elif(mouse_y >320 and mouse_y < 350):
                print_text(font,width/2-55,261,"开始游戏",black)
                print_text(font,width/2-55,321,"游戏帮助",red)
                if click:
                    help_interface = True
                    main_interface = False
            else:
                print_text(font,width/2-55,261,"开始游戏",black)
                print_text(font,width/2-55,321,"游戏帮助",black)
        else:
            print_text(font,width/2-55,261,"开始游戏",black)
            print_text(font,width/2-55,321,"游戏帮助",black)
        click = False
        
    if help_interface:                              #    enter help interface
        for event in pygame.event.get():            #    get game event messages
            if event.type == QUIT:                  #    click close
                help_interface = False
                main_interface = True               #    return main interface
        keys = pygame.key.get_pressed()             #    get the key_pressed message
        if keys[K_SPACE]:                           #    pressed SPACE key
            help_interface = False
            main_interface = True
        screen.fill(blue)
        game_help()
        
    if grade_interface:                              #    enter help interface
        for event in pygame.event.get():            #    get game event messages
            if event.type == QUIT:                  #    click close
                grade_interface = False
                main_interface = True               #    return main interface
            elif event.type == MOUSEMOTION:
                mouse_x,mouse_y = event.pos         #    get the position of mouse
            elif event.type == MOUSEBUTTONDOWN:
                click = True
                
        screen.fill((0,100,0))
        
        if(mouse_x > width/2-85 and mouse_x < width/2+85):
            if(mouse_y > 265 and mouse_y < 285):
                print_text(font,width/2-55,261,"简  单",red)
                print_text(font,width/2-55,321,"中  等",black)
                print_text(font,width/2-55,381,"困  难",black)
                if click:
                    game_interface  = True
                    grade_interface = False
                    target = int(target*0.5)

            elif(mouse_y >320 and mouse_y < 350):
                print_text(font,width/2-55,261,"简  单",black)
                print_text(font,width/2-55,321,"中  等",red)
                print_text(font,width/2-55,381,"困  难",black)
                if click:
                    game_interface  = True
                    grade_interface = False
                    target = 300
                    
            elif(mouse_y >390 and mouse_y < 420):
                print_text(font,width/2-55,261,"简  单",black)
                print_text(font,width/2-55,321,"中  等",black)
                print_text(font,width/2-55,381,"困  难",red)
                if click:
                    game_interface  = True
                    grade_interface = False
            else:
                print_text(font,width/2-55,261,"简  单",black)
                print_text(font,width/2-55,321,"中  等",black)
                print_text(font,width/2-55,381,"困  难",black)
        else:
            print_text(font,width/2-55,261,"简  单",black)
            print_text(font,width/2-55,321,"中  等",black)
            print_text(font,width/2-55,381,"困  难",black)
        click = False
        
    
    
    
    if game_interface:
        if not click:
            for event in pygame.event.get():            #    get game event messages
                if event.type == QUIT:                  #    click close
                    sys.exit()                          #    exit game
                if event.type == MOUSEBUTTONDOWN:
                    click = True
                    if clock_start == 0:
                        clock_start = time.perf_counter()
                    player.down = True
            keys = pygame.key.get_pressed()             #    get the key_pressed message
            if keys[K_ESCAPE]:                          #    pressed ESC key
                sys.exit()                              #    exit
            if keys[K_a]:
                player.left = True
                player.right = False
                player._x -= 0.2
                if player._x <= 0:
                    player._x = 0
            if keys[K_d]:
                player.left = False
                player.right = True
                player._x += 0.2
                if player._x >= width-55:
                    player._x = width-55
        if click:
            for event in pygame.event.get():            #    get game event messages
                if event.type == QUIT:                  #    click close
                    sys.exit()
            if player.down:
                player._y += player._vy
                for i in golds:
                    i.get(player._x,player._y)
                    if i.select:
                        player._vy  = i._vy
                        player.down = False
                        player.up   = True
                        break
                if player._y >= height:
                    player.down = False
                    player.up = True
            if player.up:
                player._y -= player._vy
                for i in golds:
                    if i.select:
                        i._y -= i._vy
                        break
                if player._y <= 100:
                    player._y = 100
                    for i in golds:
                        if i.select:
                            i.exit = False
                            i.select = False
                            i._y = 0
                            score += i.score
                            player._vy = 0.5
                    player.up = False
            if (not player.down) and (not player.up):
                click = False
            
        
        
        screen.fill((0,100,0))                      #    fill screen use color
        for i in golds:
            i.draw()
        player.draw()
        pygame.draw.rect(screen,black,(0,95,width,5))       #    draw the land at x = 95
        if clock_start != 0:
            Total_time = 120.0 - int(time.perf_counter() - clock_start)
        print_text(font,width-150,10,"时间:" + str(Total_time))
        if Total_time <= 10.0:
            print_text(font,width-150,10,"时间:" + str(Total_time),(255,0,0)) 
        print_text(font,0,10,"得分为：" + str(score) + " / " +str(target))
        if Total_time <= 0:
            game_interface = False
            result_interface = True
    
    if result_interface:                              #    enter help interface
        for event in pygame.event.get():            #    get game event messages
            if event.type == QUIT:                  #    click close
                sys.exit()
        keys = pygame.key.get_pressed()             #    get the key_pressed message
        if keys[K_SPACE]:                           #    pressed SPACE key
            result_interface = False
            main_interface = True
        screen.fill((0,0,100))
        if score < target:
            print_text(font1,width/2 - 110,height/2 -100,"游戏失败")
            print_text(font,200,300,"按空格键返回主菜单，或者关闭游戏")
        if score >= target:
            print_text(font1,width/2 - 110,height/2 -100,"游戏胜利",(255,0,0))
            print_text(font,200,300,"按空格键返回主菜单，或者关闭游戏")
            
            
    
    pygame.display.update()                     #    update screen
    