// tree.h
#ifndef TREE_H
#define TREE_H

typedef enum{
    NODE_NUM,
    NODE_ID,
    NODE_OP,
    NODE_BOOL
}NodeClass;

typedef enum{
    INT,
    BOOL
}NodeType;

union values{
    int num;
    int boolean; 
};

union Info{
    typedef struct infoInt{
        NodeType type;
        int value;
    }infoInt;  

    typedef struct infoBool{
        NodeType type;
        int value;
    }infoInt; 

    typedef struct infoId{
        char* name;
        NodeType type;
        union values value;
    }infoId;

    typedef struct infoOp{
        char* name;
        union values value;
    };

};

typedef struct node{
    NodeClass type;
    union Info info; 
    struct node *left;
    struct node *right;
}node;

