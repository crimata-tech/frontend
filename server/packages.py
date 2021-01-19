# server/packages.py

HEADER_LENGTH = 20

    
def pull(socket, cnvrt=False):
    """ Recv a message and return type and data. If cnvrt is True and
    type is 'aud', pull returns transcribed audio. """
    msg_header = socket.recv(HEADER_LENGTH)

    if not len(msg_header):
        print("NO DATA RECEIVED")
        return False

    # Extract type and length from header.
    msg_header = msg_header.decode('ascii')
    msg_header = msg_header.strip()
    msg_attrbs = msg_header.split('-')
    msg_type = msg_attrbs[0]
    msg_length = int(msg_attrbs[1])

    # return package data object
    package = {'type': msg_type, 'data': recvall(socket, msg_length)}

    if cnvrt:
       if package['type'] == 'aud':
            package['data'] = transcribe(package['data'])

    return package

def push(socket, data):
    """ Send a message of any type. """
    encoded_data = ''.join([data, '\0']).encode('ascii')

    # makes eg. "txt-<length of msg>"
    header = '-'.join(['txt', str(len(encoded_data))])
    header = ''.join([header, '\0'])
    encoded_header = f"{header:<{HEADER_LENGTH}}".encode('ascii')

    socket.send(encoded_header + encoded_data)

def recvall(socket, length):
    data = bytearray()
    while len(data) < length:
        packet = socket.recv(length - len(data))
        if not packet:
            return None
        data.extend(packet)
    return bytes(data)

def send_all(socket, data):
    while data:
        sent = socket.send(data)
        data = data[sent:]



