# jerif api

## 1. Types
### 1.1 Error Code
* **jerif\_err**
	* definitaion

		```c
		typedef unsigned int jerif_err;
		```
	* values
		* jerif\_ok
		* jerif\_err\_generic\_error
		* jerif\_err\_invalid\_json
		* jerif\_err\_invalid\_argument
		* jerif\_err\_stack\_underflow
		* jerif\_err\_stack\_overflow
		* jerif\_err\_stack\_unsupported\_char

### 1.2 Boolean
* **jerif\_bool**
	* definition
	
		```c
		typedef unsigned int jerif_bool;
		```
	* values
		* jerif_true
		* jerif_false


## 2. Functions
### 2.1 check module
* **jerif\_check\_validation()**
    * prototype

        ```c
        jerif_err jerif_check_validation(const char* json_str);
        ```

    * description
        * check the validity of given json string

    * parameters
		* const char\*
			* a json string to be validated

	* return
		* jerif\_err


### 2.2 stack module
* **jerif\_stack\_init()**
    * prototype

        ```c
        jerif_err jerif_stack_init(jerif_stack* s);
        ```

    * description
        * initialize a jerif\_stack & get a stack handle

    * parameters
		* jerif\_stack\*
			* stack handle

	* return
		* jerif\_err

* **jerif\_stack\_push()**
    * prototype

	    ```c    
	    jerif_err jerif_stack_push(jerif_stack* s, char item);
	    ```

    * description
        * push a given character

    * parameters
		* jerif\_stack\*
			* stack handle
		* char
			* a character to be pushed

	* return
		* jerif\_err

* **jerif\_stack\_pop()**
    * prototype

	    ```c
	    jerif_err jerif_stack_pop(jerif_stack* s, char* item);
	    ```

    * description
        * pop a character on top of stack

    * parameters
		* jerif\_stack\*
			* stack handle
		* char
			* parameter to save the poped item

	* return
		* jerif\_err

* **jerif\_stack\_dump()**
    * prototype

	    ```c
	    void jerif_stack_dump (jerif_stack* s);
	    ```

    * description
        * display the contents of stack to debug

    * parameters
		* jerif\_stack\*
			* stack handle

	* return
		* void

### 2.3 detect module

* **jerif\_detect\_boolean()**
    * prototype

	    ```c
	    jerif_bool jerif_detect_boolean(const char* str);
	    ```

    * description
        * check that a given string begins with a boolean pattern (true or false)
        * REGEX\_PATTERN\_BOOLEAN   
	        `"^(true|false)(,|}|]| |\n|\r|\t){1}.*$"`

    * parameters
		* const char*
			* a string to be checked

	* return
		* jerif_bool

* **jerif\_detect\_integer()**
    * prototype

	    ```c    
	    jerif_bool jerif_detect_integer(const char* str);
	    ```

    * description
		* check that a given string begins with a integer pattern 
		* REGEX\_PATTERN\_INTEGER
			`"^[0-9]+(,|}|]| |\n|\r|\t){1}.*$"`
			
    * parameters
		* const char*
			* a string to be checked

	* return
		* jerif_bool

* **jerif\_detect\_float()**
    * prototype

	    ```c
	    jerif_bool jerif_detect_float(const char* str);
	    ```

    * description
		* check that a given string begins with a floating number pattern 
		* REGEX\_PATTERN\_FLOAT
			`"^[0-9]+(.)[0-9]+(,|}|]| |\n|\r|\t){1}.*$"`
			
    * parameters
		* const char*
			* a string to be checked

	* return
		* jerif_bool

* **jerif\_detect\_string()**
    * prototype

	    ```c
	    jerif_bool jerif_detect_string(const char* str);
	    ```

    * description
		* check that a given string begins with a string pattern 
		* REGEX\_PATTERN\_STRING
			`"^(.)*(\"){0}(,|:|}|]| |\n|\r|\t){1}.*$"`
			
    * parameters
		* const char*
			* a string to be checked

	* return
		* jerif_bool

### 2.4 etc

* **jerif\_get\_version()**
    * prototype

	    ```c
	    char* jerif_get_version(void);
	    ```

    * description
		* get the jerif version string
			
    * parameters
		* none

	* return
		* char*
			* a buffer to save the version string
