/**
 * 验证密码Jquery插件
 *
 * 密码最大长度，密码最小长度，不能为纯数字数字，不能为纯字母，必须包含其中3项要求进行验证。
 * 同时所有可验证项都是可修改，可自定义。
 *
 * 如果设置项为“FAIL”即不进行验证
 * callBack（）返回一个对象
 *
 * 使用说明：
 * $("#ii").verifyPassword({
 * 
 *       "pass":"sss",  //密码项，填写密码，必填
 *       "minLength":"6" //密码最小长度，”FAIL“不验证此项
 *       "maxLength":"8" //密码最长长度，”FAIL“不验证此项
 *       "verifyItem":"NUM,WORD,BWORD",  //验证是否含有数字，是否含有小写字母，是否含有大写字母这3项通过几项 FAIL是不验证此项
 * 
 * },function(aa){
 *       //回调函数
 *       console.log(aa)
 * })
 */
(function($){

    /*    用于统计密码是否超过3个    */
    var contNum = 0;
    var result = {};
    var settings = {
            pass:"",
            minLength:"6",
            maxLength:"FAIL",
            //验证数字，字母，大写字母
            verifyItem:"NUM,WORD,BWORD",
            // verifyItem:"FAIL",
        }
    
    $.fn.verifyPassword = function(options, callBack){

        var option = $.extend(settings, options);
    
        if(option.pass == "" || option.pass == undefined ){
            alert("请使用pass参数配置密码")
            return false;
        }

        
        if(option.minLength != "FAIL"){
            result.PASS = passMinLength(option.pass, option.minLength)
        }

        if(option.maxLength != "FAIL"){
            result.max = passMaxLength(option.pass, option.maxLength)
        }

        //密码必须保护字母，数字，特殊字符
        // passIncludeNumAndWord();
        

        if(option.verifyItem != "FAIL"){
            var strs = new Array();
            strs = option.verifyItem.split(",");
            for(var i=0;i<strs.length;i++){
                if(strs[i] == "WORD"){
                    passCountWord(option.pass);
                }
                if(strs[i] == "NUM"){
                    passCountNum(option.pass);
                }
                if(strs[i] == "BWORD"){
                    passCountBigWord(option.pass);
                }
            }

            result.verifyItem = contNum;
        }
        
        callBack(result);
    }

    /**
     * 验证密码最小长度
     * @param  {[type]} pass      [description]
     * @param  {[type]} minLength [description]
     * @return {[type]}           [description]
     */
    function passMinLength(pass,minLength){

        //判断输入的字符长度是否是小于{minLength}个字符
        if (pass.length < minLength) {
            return "FAIL";
        } else {
            return "PASS";
        }
    }

    function passMaxLength(pass, maxLength){
        //判断输入的字符长度是否是大于{maxLength}个字符
        if (pass.length > maxLength) {
            return "FAIL";
        } else {
            return "PASS";
        }
    }

    function passIncludeNumAndWord(pass){
        // if (!passwd.match(/^(?![0-9]+$)(?![a-zA-Z]+$)[0-9A-Za-z]{6,10}$/)) {
        if (passwd.match(/^(?![0-9]+$)(?![a-zA-Z]+$)[0-9A-Za-z]+$/)) {
            return "FAIL";
        } else {
            return "PASS"
        }
    }
    // function passIfNum(pass){
    //     //判断输入的字符是否为否为纯数字
    //     if (pass.match(/^[0-9]{1,}$/)) {
    //         return "FAIL";
    //     } else {
    //         return "PASS";
    //     }
    // }

    // function passIfword(pass){
    //     //判断输入的字符是全是字母
    //     if (pass.match(/[^a-zA-Z]+/)) {
    //         return "FAIL";
    //     } else {
    //         return "PASS";
    //     }
    }

    function passCountWord(pass){
        //密码中是否有小写的英文字母,若有则计数器加一
        if (pass.match(/([a-z])+/)) {
            contNum++;
        }
    }

    function passCountNum(pass){
        //密码中是否有数字,若有则计数器加一
        if (pass.match(/([0-9])+/)) {
            contNum++;
        }
    }

    function passCountBigWord(pass){
        //密码中是否有大写字母
        if (pass.match(/([A-Z])+/)) {
            contNum++;
        }
    }

    function passCountLong(pass){
        //密码极高奖励,即大于最小两倍的字符长度
        if (pass.length > minLength * 2) {
            contNum++;
        }
    }
    
})(jQuery)