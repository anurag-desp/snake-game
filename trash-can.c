int complementhit(char hit, char last_hit){
    if(hit == 'd' || hit == 'a'){
        if(last_hit != 'a' && last_hit != 'd') return 1;
        else return 0;
    }
    if(hit == 'w' || hit == 's'){
        if(last_hit != 's' && last_hit != 'w') return 1;
        else return 0;
    }

    return 0;
}

Snake* moveSnake(Snake* head, char hit){
    // Snake* new = malloc(sizeof(Snake));
    static char last_hit = 'd';
    Snake* temp = head;

    printf("hit: %c\nlast_hit: %c\n", hit, last_hit);
    int target_x, target_y;
    while(temp -> next){
        temp = temp -> next;
    }
    target_x = temp -> x_position;
    target_y = temp -> y_position;

    printf("target_x: %d\ntarget_y: %d\n", target_x, target_y);
    temp = head;

    if(complementhit(hit, last_hit)){
        if(hit == 'w'){
            if(last_hit == 'a'){
                target_x = head -> x_position;
                target_y = head -> y_position;

                temp = reverseSnake(head);
                head = temp;
            }

            while(temp){
                temp -> x_position = target_x;
                temp -> y_position = target_y--;
                temp = temp -> next;
            }
            if(last_hit == 'd' || last_hit == 'a') head = reverseSnake(head);
        }

        else if(hit == 's'){
            if(last_hit == 'a'){
                target_x = head -> x_position;
                target_y = head -> y_position;

                temp = reverseSnake(head);
                head = temp;
            }

            while(temp){
                temp -> x_position = target_x;
                temp -> y_position = target_y++;
                temp = temp -> next;
            }
        }

        else if(hit == 'a'){
            if(last_hit == 'w'){
                target_x = head -> x_position;
                target_y = head -> y_position;
                temp = reverseSnake(head);
                head = temp;
            }

            while(temp){
                temp -> y_position = target_y;
                temp ->x_position = target_x--;
                temp = temp -> next;
            }
            if(last_hit == 's' || last_hit == 'w') head = reverseSnake(head);
        }

        else if(hit == 'd'){
            if(last_hit == 'w'){
                target_x = head -> x_position;
                target_y = head -> y_position;

                temp = reverseSnake(head);
                head = temp;
            }

            while(temp){
                temp -> y_position = target_y;
                temp -> x_position = target_x++;
                temp = temp -> next;
            }
            // if(last_hit == 'w') head = reverseSnake(head);
        }

        last_hit = hit;
        return head;
    }

    else{
        if(last_hit == 'w'){
            while(temp){
                temp -> y_position--;
                temp = temp -> next;
            }
        }

        else if(last_hit == 's'){
            while(temp){
                ++temp -> y_position;
                temp = temp -> next;
            }
        }

        else if(last_hit == 'a'){
            while(temp){
                temp -> x_position--;
                temp = temp -> next;
            }
        }

        else if(last_hit == 'd'){
            while(temp){
                temp -> x_position++;
                temp = temp -> next;
            }
        }

        return head;
    }
}
