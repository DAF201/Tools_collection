local loop = {}
local task_detail = {}
local request_inprocess = {}

local looper_execution_counter = 0

task_timeout = 10


function looper()
    looper_execution_counter = looper_execution_counter + 1

    if #loop == 0 then print("loop empty") return end

    if string.find(loop[1], "modbus_request_%d%d%d%d%d") then
        if request_inprocess[loop[1]] == nil then
            request_inprocess[loop[1]] = looper_execution_counter + task_timeout
        else
            if request_inprocess[loop[1]] < looper_execution_counter then
                print("request time out: " .. loop[1])
                request_inprocess[loop[1]] = nil
                remove_from_loop(loop[1])
                return
            else
                loop[#loop + 1] = loop[1]
                table.remove(loop, 1)
                return
            end
        end
    end

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
