-- linux only
local usb = {}
local current_devices = {}
local mounted_devices = {}
local init_devices = {}
local commands = {
    ['get_mount_info'] = 'lsblk | grep sd',
    ['get_usb_drives'] = 'blkid',
    ['devices'] = '/[%a%d%p]+/[%a%d]+',
    ['console'] = '>/dev/ttySC0',
    ['usb_drive_mount_point'] = '/run/media/',
    ['rmdir'] = 'rm -r ',
    ['find'] = 'find '
}

local function split(s, delimiter)
    local result = {};

    if s ~= nil then
        for match in (s .. delimiter):gmatch('(.-)' .. delimiter) do
            table.insert(result, match);
        end
    end
    return result;
end

local function dump(o)
    if type(o) == 'table' then
        local s = '{ '
        for k, v in pairs(o) do
            if type(k) ~= 'number' then
                k = '"' .. k .. '"'
            end
            s = s .. '[' .. k .. '] = ' .. dump(v) .. ','
        end
        return s .. '} '
    else
        return tostring(o)
    end
end

local function cout(str)
    print(dump(str))
    pcall(os.execute, { 'echo ' .. dump(str) .. commands['console'] })
end

local function exists(file)
    local ok, err, code = os.rename(file, file)
    if not ok then
        if code == 13 then
            return true
        end
    end
    return ok, err
end

local function isdir(path)
    return exists(path .. '/')
end

local function command_execution(cmd)
    local pipe_in = assert(io.popen(cmd, 'r'))
    local result = assert(pipe_in:read('*a'))
    pipe_in:close()
    return result
end

local function get_devices()
    local devices_buffer = {}
    for index, usb in pairs(split(command_execution(commands['get_usb_drives']), '\n')) do
        if usb ~= '' then
            devices_buffer[#devices_buffer + 1] = { string.gmatch(usb, commands['devices'])() }
        end
    end

    return devices_buffer
end

local function usb_drive_mount()
    if not isdir('/run/media/') then
        command_execution('mkdir /run/media')
    end
    local result = {}
    for k, v in pairs(current_devices) do
        if (string.gmatch(v[1], '/dev/sd%a%d')()) then
            local usb_drive_name = string.gmatch(v[1], 'sd%a%d')()
            if not isdir(commands['usb_drive_mount_point'] .. usb_drive_name) then
                command_execution('mkdir ' .. commands['usb_drive_mount_point'] .. usb_drive_name)
            end
            command_execution('mount ' .. v[1] .. " " .. commands['usb_drive_mount_point'] .. usb_drive_name)
            cout("mounting " .. v[1] .. " to " .. commands['usb_drive_mount_point'] .. usb_drive_name)
            mounted_devices[v[1]] = v[1]
            result[#result + 1] = commands['usb_drive_mount_point'] .. usb_drive_name
        end
    end
    return result
end

local function usb_drive_umount(usb_drive_mount_point)
    command_execution('umount ' .. usb_drive_mount_point)
    local usb_drive_name = string.gmatch(usb_drive_mount_point, "sd%a%d")()
    command_execution(commands['rmdir'] .. "/run/media/" .. usb_drive_name)
    cout("umounting usb drive on " .. usb_drive_mount_point)
    mounted_devices[usb_drive_mount_point] = nil
end

function usb:init()
    init_devices = get_devices()
end

function usb:get_new_devices()
    os.execute('sleep 1')
    current_devices = get_devices()
    local result = {}
    if #current_devices == #init_devices and mounted_devices ~= {} then
        for k, v in pairs(mounted_devices) do
            usb_drive_umount(v)
        end
    end
    for i = 0, #current_devices, 1 do
        if init_devices[i] == nil and current_devices[i] ~= nil then
            result[#result + 1] = current_devices[i]
            if mounted_devices[current_devices[i][1]] == nil then
                usb_drive_mount()
            end
        end
    end
    return result
end

usb:init()

while (1) do
    usb:get_new_devices()
end
