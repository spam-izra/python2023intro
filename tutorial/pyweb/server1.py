# Импорт модуля
import socket

# Адрес интерфейс, на котором мы ожидаем подключения
# '' или '0.0.0.0' означает, что мы смотрим на все
# сетевые интерфейсы компьютера (ведь мы помним, что компьютер
# может иметь несколько сетевых карт и у каждой свой адрес)
HOST = ''                 

# Порт, который мы прослушиваем 
PORT = 50007

# Используем менеджер контекста
# Альтернатива - это создать сокет 
# s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Но в конце его нужно закрыть, иначе другие программы не смогут работать
# с данным портом
# s.close()

# AF_INET - это означает IPv4
# AF_INET6 - IPv6
# SOCK_STREAM - TCP
# SOCK_DGRAM - UDP
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    # Привязываем сокет к интерфейсу и порту на нем
    s.bind((HOST, PORT))
    # Указываем, что это СЛУШАЮЩИЙ сокет, то есть он принимает 
    # соединения. В скобках указывает число одновременных соединения,
    # которые принимает данный сокет. Если соединений больше, то сокет 
    # будет откланять новые соединения.
    s.listen(1)
    
    print("Listenning %s:%s" % (HOST, PORT))
    print("Ctrl+C to stop server")
    
    # А тут уже хитрее, мы переходим в режим ожидания нового соединения.
    # Когда оно происходит, данный метов возвращает НОВЫЙ сокет,
    # который готов к приему и передаче данных.
    # Также возвращается адрес сокета клиента (на удаленной машине).
    conn, addr = s.accept()
    
    # Также используем менеджер контекста, что не пришлось вручную
    # закрывать сокет 
    # conn.close()
    with conn:
        print('Connected by', addr)
        while True:
            # получить МАКСИМУМ 1024 байт данных
            # может придти и меньше. Код блокируется до тех пор,
            # пока данные не будут получены
            data = conn.recv(1024)
            # Если получили пустую строку, то это означает,
            # что соединение было закрыто. Во всех остальных случаях
            # вы получите исключение.
            if not data: break
            
            # отправляем данные обратно
            conn.sendall(data)
