# rand() function
- Under <stdlib.h> function
- rand() in c generates a psudo-random number. It means that it generates a random number using an or several algorithms(duh!) so that, the number generated are in no way related to each other. But each time you run the program, you will get the same random number of sequence of random numbers.

- ## srand
    - s: seed
    - here you can provide a value as a parameter in the function which will act as a seed
    - what does that mean?
    ```
    // suppose we want to create out our random function

    #include <stdio.h>
    int myRandomNumber(){
        static int seed = 10;
        static int random_operation = 0;
        random_operation = random_operation % 4;
        switch (random_operation)
        {
        case 0:
            seed += 2;
            break;
        case 1:
            seed /= 4;
            break;
        case 2:
            seed *= 5;
            break;
        case 3:
            seed = seed ^ 4;
            break;
        }

        random_operation++;
        return seed;
    }

    int main(void){
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());
        printf("%d\n", myRandomNumber());

        return 0;
    }
    ```
    - In the above program, you can notice that the function can kinda generate a random number using that stupid algorithm. This is roughly how to real rand() function works (for the sake of this explanation).
    - In this program, everytime you call the function you will get a random number, but everytime you run the code you get the same result. This is because we are always starting with 10 (seed). But if we everytime we give a different seed value, we will get a different result.
    - This is kinda how we use **srand** function. The most used seed value is **time()**.     

---
# Passing a multidimensional array as an argument to a function
- for 1D array, it is quite simple.
```
    // syntax:
    int passArray(int arr[]){
        // body
        return integer;
    }
```

- but for multidimensional arrays, first dimension isn't needed to be specified but the subsequent dimensions have to be given
```
    // syntax:
    int passArray(int arr[][50]){
        // body;
        return integer;
    }
```

## Pass By Value/Reference with Pointers
- This was probably the best learning I got from this project. 
- So, as we know, in C we **pass by value** to a function by default. So, when you are passing, let's say, the head of a linked list, you are just passing the value(in this case, the address of the head node in **heap**). Yes, the **VALUE** because, surprise surprise, **pointers are just variables**. So, when you insert at the beginning or destroy the head of a list, you won't be able to see the changes unless you return the new head. Because, as I mentioned, the head still has the old node's address stored in it, because you **JUST passed the address as a VALUE to the function**
- In order to get the new changes, there are two things you can do:
    - Retrun the new head.
    - Pass the head **by reference** to the function. This will change the value directly inside the head.

> **Code Examples to explain it better**
#### Code 1 (Bad)
```
void destroyList(Node* _head){
    Node* temp = _head;
    Node* pre = NULL;
    while(temp){
        pre = temp;
        temp = temp -> next;
        free(pre);
    }
    _head = NULL;
}

// The Problem: Here, you are passing the value
// inside the head (which is an address of a structure called Node, in heap)
// So, when you're freeing the nodes in the list,
// they are indeed getting freed, but the address
// of the head node remains inside the 
// head(this head is the variable that was passed as argument in the destroy function)
// even if you do _head = NULL;
// (_head is a local variable to the function, so no changes to the callie part)
```

#### Code 2 (Good)
```
void destroyGood(Node** _head){
    Node* temp = *_head;
    Node* pre = NULL;

    while(temp){
        pre = temp;
        temp = temp -> next;
        free(pre);
    }

    *_head = NULL;
}

// Here, you are passing the head as reference.
// So, after you free all the nodes, you can simply update
// the head directly, without needing to return anything.
```

- This seems quite obvious, once I figured it out!
# Philosophical Learning
- You just have to keep doing it and eventually, you'll figure it out.