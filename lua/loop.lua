local loop = {}
local task_detail = {}

looper_execution_counter = 0

function looper()
    looper_execution_counter = looper_execution_counter + 1

    if #loop == 0 then print("loop empty") return end

    local task_repeat  = task_detail[loop[1]][1] -- type: 0 repeatedly, 1 one time
    local func_pointer = task_detail[loop[1]][2] -- just the function
    local arg1         = task_detail[loop[1]][3]
    local arg2         = task_detail[loop[1]][4]
    local arg3         = task_detail[loop[1]][5]
    local arg4         = task_detail[loop[1]][6]
    local arg5         = task_detail[loop[1]][7]

    local statu, error = pcall(func_pointer, arg1, arg2, arg3, arg4, arg5)

    if not statu then
        print(error)
        return
    end

    if task_repeat ~= 1 then
        loop[#loop + 1] = loop[1]
    end

    table.remove(loop, 1)

    return
end

function append_to_loop(id, task_repeat, func, arg1, arg2, arg3, arg4, arg5)
    if task_detail[id] ~= nil then
        return false
    end

    loop[#loop + 1] = id
    task_detail[id] = { task_repeat, func, arg1, arg2, arg3, arg4, arg5 }

    return true
end

function remove_from_loop(id)
    if task_detail[id] == nil then
        return false
    end

    for k, v in pairs(loop) do
        if v == id then
            table.remove(loop, k)
            task_detail[v] = nil
        end
    end
end

function dump(o)
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

append_to_loop("print1", 0, print, 1, 2, 3, 4, 5)
append_to_loop("print2", 0, print, 6, 7, 8, 9, 0)
append_to_loop("print3", 1, print, 11, 12, 13, 14, 15)

while true do
    looper()
    if looper_execution_counter > 10 then
        remove_from_loop("print1")
    end

    if looper_execution_counter > 10 then
        remove_from_loop("print2")
    end

    if looper_execution_counter > 10 then
        remove_from_loop("print3")
    end

    if looper_execution_counter > 4 then
        append_to_loop("print4", 1, print, 16, 17, 18, 19, 20)
    end
    os.execute("powershell sleep 1")
end
