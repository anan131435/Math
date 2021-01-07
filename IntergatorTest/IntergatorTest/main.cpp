//
//  main.cpp
//  IntergatorTest
//
//  Created by 韩志峰 on 2020/12/12.
//  Copyright © 2020 kuaishou. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>
#include <queue>
#include <math.h>
#include <unordered_map>
#include <string>
#include <math.h>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x),left(NULL),right(NULL){}
};

struct ListNode{
    int val;
    ListNode *next;
    ListNode() : val(0),next(nullptr) {}
};

class Solution {
public:
    
    ListNode *mergeTwoList(ListNode *list1, ListNode* list2){
        if (list1 == nullptr) {
            return  list2;
        }
        if (list2 == nullptr) {
            return  list1;
        }
        if (list1 -> val < list2 -> val) {
            list1 -> next = mergeTwoList(list1 -> next, list2);
            return  list1;
        }else{
            list2 -> next = mergeTwoList(list2 -> next, list1);
            return  list2;
        }
        
    }
};

class PathSumH{
private:
    vector<vector<int>>  result;
    vector<int> path;
public:
    vector<vector<int>> pathsum(TreeNode *root, int sum){
        return result;
    }
    void helper(TreeNode *root, int sum){
        if (!root) {
            return;
        }
        sum = sum - root -> val;
        if (root -> left == nullptr && root -> right == nullptr ) {
            if (sum == 0) {
                path.push_back(root -> val);
                result.push_back(path);
                path.pop_back();
            }
            return;
        }
        path.push_back(root -> val);
        helper(root -> left, sum);
        helper(root -> right, sum);
        path.pop_back();
        
    }
};
// 17.12 把二叉搜索树转换为单向链表 二叉搜索树，按照中序遍历是升序的
/*
 要求是原址修改，即要直接利用这些已经存在的节点空间。修改这些节点的指向来得到单向链表。
 
 
 */
// 124 二叉树中的最大路径和  DFS
/*
 1. base case
 2. 向子问题要答案
 3. 利用子问题答案 构建当前问题 答案
 4. 若有必要 做一些额外处理
 5. 返回答案给父问题
 
 */
class Solution3 {
private:
    int maxValue = INT_MIN;
public:
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return  maxValue;
    }
    int dfs(TreeNode *root){
        if (!root) {
            return  0;
        }
        int left = dfs(root -> left);
        int right = dfs(root -> right);
        left = left > 0 ? left : 0;
        right = right > 0 ? right : 0;
        maxValue = max(maxValue,left + right + root -> val);
        return  max(left, right) + root -> val;
    }
};

class Solution1{
private:
    vector<vector<int>> ret;
public:
    vector<vector<int>> pathSum(TreeNode *root,int sum){
        if (root == nullptr) {
            return ret;
        }
        ret.clear();
        int cursum = 0;
        vector<int> temp;
        recursive_find(root, cursum, sum, temp);
        return ret;
    }
    void recursive_find(TreeNode *pNode, int cursum, int aim, vector<int> temp){
        if (pNode -> left == nullptr && pNode -> right == nullptr) {
            //返回条件
            if (cursum + pNode -> val == aim) {
                temp.push_back(pNode -> val);
                ret.push_back(temp);
                temp.pop_back();
            }
            return;
        }
        cursum = cursum + pNode -> val;
        temp.push_back(pNode -> val);
        if (pNode -> left != nullptr) {
            recursive_find(pNode -> left, cursum, aim, temp);
        }
        if (pNode -> right != nullptr) {
            recursive_find(pNode -> right, cursum, aim, temp);
        }
        temp.pop_back();
        cursum = cursum -pNode -> val;
    }
};

// 111 二叉树最小深度
int mintDepth(TreeNode *root){
    
    if (!root) {
        return 0;
    }
    if (root -> left == nullptr && root -> right == nullptr) {
        return 1;
    }
    int leftMin = mintDepth(root -> left);
    int rightMin = mintDepth(root -> right);
    if (root -> left == nullptr || root -> right == nullptr) {
        return leftMin + rightMin + 1;
    }
    int minDepth = leftMin < rightMin ? leftMin : rightMin;
    return minDepth + 1;
    
}
/*
int minDepthTree(TreeNode *root){
    if (!root) {
        return 0;
    }
    if (root -> left ==  nullptr && root -> right == nullptr) {
        return 1;
    }
    int leftDepth = mintDepth(root -> left);
    int rightDepth = mintDepth(root -> right);
    if (root -> left == nullptr || root -> right == nullptr) {
        return  leftDepth + rightDepth + 1;
    }
    int minth = leftDepth < rightDepth ? leftDepth : rightDepth;
    return minth + 1;
} */
//112 路径总和
/* 给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有的节点值相加等于目标和
 是否存在 这样一条路径，其实是遍历所有可能(层序遍历)
 思路： 核心思想是对树进行一次遍历，在遍历时记录从根节点到当前节点的路径和，以防止重复计算。
 广度优先搜索： 使用两个队列，分别存储将要遍历的节点和根节点到这些节点的路径和。
*/
bool  haspathsum(TreeNode *root,int sum){
    if (!root) {
        return false;
    }
    
    queue<TreeNode *> nodeQueue;
    queue<int> valueQueue;
    nodeQueue.push(root);
    valueQueue.push(root -> val);
    while (!nodeQueue.empty()) {
        TreeNode *current = nodeQueue.front();
        nodeQueue.pop();
        int value = valueQueue.front();
        valueQueue.pop();
        
        if (current -> left == nullptr && current -> right == nullptr) {
            if (value == sum) return true;     // while 退出条件
            continue;
        }
        if (current -> left != nullptr) {
            nodeQueue.push(current -> left);
            valueQueue.push(current -> left -> val + value);
        }
        if (current -> right != nullptr) {
            nodeQueue.push(current -> right);
            valueQueue.push(current -> right -> val + value);
        }
    }
    return false;
    
}
bool  hasPathSumValue(TreeNode *root, int sum){
    if (!root) {
        return false;
    }
    if (root -> left == nullptr && root -> right == nullptr) {
        return root -> val == sum;
    }
    return haspathsum(root -> left, sum - root -> val) || haspathsum(root -> right, sum - root ->val);
}

/*
 给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

 说明: 叶子节点是指没有子节点的节点。
 思路： 是否存在，即要遍历所有可能性，采用层序遍历，同时保证每次遍历都是一条路径
 思路：当前节点值value,那么 当前节点到叶子节点值之和 为 sum - value
 */
bool haspathEqualToSum(TreeNode *root, int  sum){
    if (!root) {
        return false;
    }
    if  (root -> left == nullptr && root -> right == nullptr) {
        return sum == root -> val;
    }
    return haspathsum(root -> left, sum - root -> val) || haspathsum(root -> right, sum - root -> val);
}
// 113 路径总和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径










class PathSum{
    vector<vector<int>>  result;
    vector<int> path;
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        pathHelper(root, sum);
        return result;
    }
    void pathHelper(TreeNode *root, int sum){
        if (!root) {
            return;
        }
        path.emplace_back(root -> val);
        sum = sum - root -> val;
        if (root -> left == nullptr && root -> right == nullptr && sum == 0) {
            result.push_back(path);
        }
        pathHelper(root -> left, sum);
        pathHelper(root -> right, sum);
        path.pop_back();
    }
};
/*
vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> result;
    if (!root) {
        return  result;
    }
    queue<TreeNode *> nodeQueue;
    vector<int> valueVector;
    nodeQueue.push(root);
    valueVector.push_back(root -> val);
    while (!nodeQueue.empty()) {
        TreeNode *current = nodeQueue.front();
        nodeQueue.pop();
        int count = valueVector.size();
        int tmpSum = 0;
        for (int i = 0; i < count; i ++) {
            tmpSum = tmpSum + valueVector[i];
        }
        if (current -> left == nullptr && current -> right == nullptr && tmpSum == sum) {
            result.push_back(valueVector);
        }
        if (current -> left) {
            nodeQueue.push(current -> left);
            valueVector.push_back(current -> left -> val);
        }
        if (current -> right) {
            nodeQueue.push(current -> right);
            valueVector.push_back(current -> right ->val);
        }
    }
    return result;
}*/

class Solution5{
private:
    vector<vector<int>> result;
    vector<int> path;
    int title = 0;
    vector<int> valueSum;
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        helper(root, sum);
        return result;
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return  result;
    }
    void inorder(TreeNode *root,vector<int>& result){
        if (!root) {
            return;
        }
        inorder(root -> left, result);
        result.push_back(root -> val);
        inorder(root -> right, result);
    }
    // 只要根节点的 左右子树是镜像对称的 那么就是镜像对称树
    // 怎么判断两棵树是镜像对称的
    bool isSymmetric(TreeNode* root) {
        return  isSymmetricHelper(root, root);
        
    }
    bool isSymmetricHelper(TreeNode *root,TreeNode *root1){
        if (!root && !root1) {
            return  true;
        }
        if (root == nullptr || root1 == nullptr) {
            return  false;
        }
        return (root -> val == root1 -> val) && isSymmetricHelper(root -> left, root1 -> right) && isSymmetricHelper(root -> right, root1 -> left);
    }
    /*
     3  9
     9  3 15
     */
    
    void helper(TreeNode *root,int sum){
        if (!root) {
            return;
        }
        sum = sum - root -> val;
        path.emplace_back(root -> val);
        if (root -> left == nullptr && root -> right == nullptr && sum == 0) {
            result.emplace_back(path);
        }
        helper(root -> left, sum);
        helper(root -> right, sum);
        path.pop_back();
    }
    // 563 二叉树的坡度
    /*
       计算整棵树的坡度之和，我们可以利用递归函数计算每个节点的坡度
       1.要计算每个节点的坡度，就要先计算该节点的左子树节点之和 和 右子树结点之和
       2.左子树节点之和 = 左子树根节点 + 左子树的左子树的节点之和 + 左子树的右子树的节点之和
     3.继续分解下去，知道分解到空树，空树的节点之和为0
     */
    int findTilt(TreeNode* root) {
        traverse(root);
        return title;

    }
    int  traverse(TreeNode *root){
        if (!root) {
            return 0;
        }
        int left = traverse(root -> left);
        int right = traverse(root -> right);
        title = title + abs(left - right);
        return left + right + root -> val;
    }
    // 1 -> 2 ->  3 ->  4
    // 2  -> 1 ->  4  -> 3
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head -> next == nullptr) {
            return  head;
        }
        ListNode *newHead = head -> next;
        head -> next = swapPairs(newHead -> next);
        newHead -> next = head;
        return  newHead;
    }
    




    
    
};




















// {1,2,3,4,5,#,6,#,#,7,8}
/*
     1
    / \
   2   3
  / \   \
 4   5   6
    / \
   7   8
 */
TreeNode *createTree(vector<int> list,int start){
    if (list[start] == '#') {
        cout << "# is " << start << endl;
        return nullptr;
    }
    TreeNode *root = new TreeNode(list[start]);
    int lnode = 2 * start + 1;
    int rnode = 2 * start + 2;
    if (lnode > list.size() - 1) {
        root -> left = nullptr;
    }else{
        root -> left = createTree(list, lnode);
    }
    if (rnode > list.size() - 1) {
        root -> right = nullptr;
    }else{
        root -> right = createTree(list, rnode);
    }
    return root;
}












void _quickSort(int arr[],int left, int right){
    if (left >= right) {
        return;
    }
    int i = left;
    int j = right;
    int flag = left;
    while (i < j) {
        while (arr[j] > arr[flag] && (i < j)) {
            j --;
        }
        while (arr[i] < arr[flag] && (i < j)) {
            i ++;
        }
        if (i < j) {
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    int temp = arr[flag];
    arr[flag] = arr[i];
    arr[i] = temp;
    _quickSort(arr, left, i -1);
    _quickSort(arr, i + 1, right);
}
void quickSort(int arr[], int n){
    _quickSort(arr, 0, n -1);
}







int main(int argc, const char * argv[]) {
    int arr[5] = {5,4,3,2,1};
    quickSort(arr, 5);
    for (int i = 0; i < 5; i ++) {
        cout << arr[i] << endl ;
    }
//    //默认是大顶堆
//    priority_queue<int> a;
//
//    //等同于 priority_queue<int,vector<int>, less<int> > a;
//    //小顶堆
//    priority_queue<int, vector<int>, greater<int>> c;
//
//    priority_queue<string> b;
//
//    for (int i = 0; i < 5; i ++) {
//        a.push(i);
//        c.push(i);
//    }
//    while (!a.empty()) {
//        cout << a.top() << ' ';
//        a.pop();
//    }
//    cout << endl;
//    while (!c.empty()) {
//        cout << c.top() << ' ';
//        c.pop();
//    }
//    cout << endl;
    
    
    return 0;
}
/*
 priority_queue
 top 访问头元素
 empty 队列是否是空
 size  返回队列内元素个数
 push  插入元素到队尾
 pop  弹出队头元素
 swap 交换内容
 emplace 原地构造一个元素并插入队列
 
 */
