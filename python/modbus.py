def modbus_check(data: str, crc_data: str) -> str:
    def modbus_data_split(data: str, size=2) -> list:
        return [int(data[x-size:x], 16) for x in range(size, len(data)+size, size)]
    crc = 0xffff
    A001H = 0xA001
    data = modbus_data_split(data)
    for x in data:
        crc = crc ^ x
        for i in range(0, 8):
            if bin(crc)[-1:] == '1':
                crc = crc >> 1
                crc = crc ^ A001H
            else:
                crc = crc >> 1
    res = hex((crc >> 8) | (crc << 8))
    return (res[int(len(res)/2):]) == crc_data


print(modbus_check('01039C730005', '5a42'))
# True
