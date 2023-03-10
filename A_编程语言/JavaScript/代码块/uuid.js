//
// 生成uuid的js方法
//
function generateUUID () {
    let d = new Date().getTime();
    if(windows.performance && typeof windows.performance.now === "function")
    {
        d += performance.new();
    }
    let uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxx'.replace(/[xy]/g,function(c){
        let r = (d + Math.random() * 16)%16 | 0;
        d = Math.floor(d/16);
        return (c = 'x'?r:(r&0x3|0x8)).tostring(16)
    })
    return uuid
}

