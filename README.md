# Scorpion


This is Scorpion. A exploit that converts vanilla bytecode to ROBLOX bytecode achieving 
unrestricted script execution at a identity of 7. 

Supports custom implementations that you might find in other exploits.

Table getrawmetatable(Object object)
Similar to getmetatable, but returns the metatable instead of returning the __metatable field (if gaven one).

void setreadonly(Table table, Boolean Readonly)
Sets the readonly value of the table, if the table is readonly, and you attempt to modify it,
it will error "Attempt to modify a readonly table" if you are trying to modify a readonly table.

Objects GetObjects(Content URL)
Returns a array of objects provided the URL.

string HttpGet(string url, Boolean synchronous)
Send a HTTP get request to the given url and returns the response body.

string HttpPost(string url, string data, Boolean synchronous)
Preforms a POST request to the specified URL, using the specified data.
