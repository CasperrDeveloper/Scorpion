# Scorpion


This is Scorpion. A exploit that converts vanilla bytecode to ROBLOX bytecode achieving 
unrestricted script execution and executes scripts at a identity of 7.

Supports custom implementations that you might find in other exploits.

```lua
Table getrawmetatable(Object object)
--Similar to getmetatable, but returns the metatable instead of returning the __metatable field (if gaven one).
```

```lua
void setreadonly(Table table, bool Readonly)
--Sets the readonly value of the table, if the table is readonly, and you attempt to modify it,
--it will error "Attempt to modify a readonly table" if you are trying to modify a readonly table.
```

```lua
Objects GetObjects(Content URL)
--Returns a array of objects accompanied by the URL.
```

```lua
string HttpGet(string url, bool synchronous)
--Send a HTTP get request to the given url and returns the response body.
--If the url contains 'getauthticket' the script will return 'Malicious site'.
```
```lua
string HttpPost(string url, string data, bool synchronous)
--Preforms a POST request to the specified URL, using the specified data.
--If the url contains 'getauthticket' the script will return 'Malicious site'.
```

```lua
bool checkcaller(None)
--Returns true if the script is being ran by Scorpion
```
