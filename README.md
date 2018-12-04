# Scorpion


This is Scorpion. A exploit that converts vanilla bytecode to ROBLOX bytecode achieving 
unrestricted script execution at a identity of 7. 

Supports custom implementations that you might find in other exploits.

Table getrawmetatable(Object Obj)
Similar to getmetatable, but does not check for a __metatable field or invoke it at all. It is similar or equivalent to debug.getmetatable

void setreadonly(Table table, Boolean Readonly)
Sets the readonly value of the table, if the table is readonly, and you attempt to modify it,
it will error "Attempt to modify a readonly table" if you are trying to modify a readonly table.

Objects GetObjects(Content url )
Returns a array of objects

string HttpGet(string url, bool synchronous)
Send a HTTP get request to the given url and returns the response body

string HttpPost(string url, string data, bool synchronous)
Preforms a POST request to the specified URL, using the specified data.
