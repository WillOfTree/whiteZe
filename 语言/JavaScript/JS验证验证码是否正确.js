//验证码代码，生成验证码的id是checkcode
//验证码的输入框id是inputcode
var code;
function createCode() {
    code = "";
    var codeLength = 4; //验证码的长度
    var checkCode = document.getElementById("checkCode");
    var codeChars = new Array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'); //所有候选组成验证码的字符，当然也可以用中文的
    for (var i = 0; i < codeLength; i++)
    {
        var charNum = Math.floor(Math.random() * 52);
        code += codeChars[charNum];
    }
    // code = "<span>" + code + "<span>";
    if (checkCode)
    {
        //这里添加验证码的样式
        checkCode.className = "code my-yanzhengma";
        checkCode.innerHTML = code;
    }
}

function validateCode()
{
    //验证码输入框的id
    var inputCode = document.getElementById("inputCode").value;
    if (inputCode.length <= 0) 
    {
        alert("请输入验证码！");
    }
    else if (inputCode.toUpperCase() != code.toUpperCase()) 
    {
        alert("验证码输入有误！");
        createCode();
    }
    else 
    {
        alert("验证码正确！");
    }        
}

/*验证码样式*/
.code{
    /* 背景图片 */
    /* background:url(code_bg.jpg); */
    font-family:Arial;
    font-style:italic;
    color:rgb(75, 168, 51);
    font-size:20px;
    border:0;
    padding:0px;
    /* letter-spacing:3px; */
    font-weight:bolder;
    /* float:left; */
    /* cursor:pointer; */
    /* width:150px; */
    /* height:60px; */
    /* line-height:45px; */
    /* text-align:center; */
    /* vertical-align:middle; */
}