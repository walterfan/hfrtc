function random_str()
{
    var text = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for( var i=0; i < 8; i++ )
        text += possible.charAt(Math.floor(Math.random() * possible.length));

    return text;
}

var array = new Array();
for ( var i = 0; i < 10000; i++) 
{
	array[array.length] = random_str();
}
debug_trace("begin sort and reverse array which length=" + array.length );

array.sort();
array.reverse();

debug_trace("done, first element=" + array[0]+ ", " + "last element=" + array[array.length-1] );
