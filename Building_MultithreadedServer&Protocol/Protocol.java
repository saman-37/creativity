public interface Protocol {
    int PORT = 1000;
    int ADD_ITEM = 1;
    int CHECK_INVENTORY = 2;
    int TAKE_ITEM = 3;
    int GET_THRESHOLD=4;
    int QUIT = 5;
    int SUCCEED = 6;
    int FAILED = 7;
    int CLOSED = 8;

}

/*
Client side:					Server side:
----------------------------------------------
ADD_ITEM item# n		        SUCCEED / FAILED
CHECK_ INVENTORY item#		    SUCCEED n / FAILED
TAKE_ITEM item# n               SUCCEED n / FAILED
GET_THRESHOLD n 			    SUCCEED response / FAILED
QUIT							CLOSED
----------------------------------------------
item: String
n: int
*/