/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution 
{
    private:
        inline TreeNode *GetSuccessor(TreeNode *Del) const noexcept
        {
            TreeNode *SuccessorParent = Del;
            TreeNode *Successor = Del;
            TreeNode *Curr = Del->right;
            while(Curr)
            {
                SuccessorParent = Successor;
                Successor = Curr;
                Curr = Curr->left;
            }   // while
            if(Successor != Del->right){
                SuccessorParent->left = Successor->right;
                Successor->right = Del->right;
            }   // if
            return Successor;
        }   // GetSuccessor
    
        inline TreeNode *Del(TreeNode *Start, TreeNode *Parent, TreeNode *Curr, int key, bool LR) const noexcept
        {
            if(Curr)
            {
                if(Curr->val != key)
                {
                    if(Curr->val > key)
                        return Del(Start, Curr, Curr->left, key, 0);
                    else
                        return Del(Start, Curr, Curr->right, key, 1);
                }   // if
                else
                {
                    if(Parent == Curr)
                    {  // root deletion
                        if(!Curr->left && !Curr->right)
                        { // root as leaf
                            delete Curr;
                            Curr = Parent = nullptr;
                            return Curr;
                        }   // if
                        else if(Curr->left && !Curr->right)
                        { // root with one left child
                            TreeNode *temp = Parent;
                            Curr = Curr->left;
                            delete temp;
                            return Curr;
                        }   // else if
                        else if(Curr->left && !Curr->right)
                        { // root with one right child
                            TreeNode *temp = Parent;
                            Curr = Curr->right;
                            delete temp;
                            return Curr;
                        }   // else if
                        else
                        {  // root with 2 chlidren
                            TreeNode *Temp = Parent;
                            TreeNode *S = GetSuccessor(Parent);  // find Successor
                            Parent = S;
                            S->left = Curr->left;
                            delete Temp;
                            return Parent;
                        }   // else
                    }   // if
                    else
                    {  // inner node, or leaf deletion
                        if(!Curr->left && !Curr->right)
                        { // leaf deletion
                            if(LR)
                            { // right leaf
                                delete Parent->right;
                                Parent->right = nullptr;
                                return Start;
                            }   // if
                            else
                            {  // left leaf
                                delete Parent->left;
                                Parent->left = nullptr;
                                return Start; 
                            }   // else
                        }   // if
                        else if(Curr->left && !Curr->right)
                        { // inner node with 1 left child
                            if(LR)
                            { // right node
                                TreeNode *Temp = Parent->right;
                                Parent->right = Curr->left;
                                delete Temp;
                                return Start;
                            }   // if
                            else
                            {  // left node
                                TreeNode *Temp = Parent->left;
                                Parent->left = Curr->left;
                                delete Temp;
                                return Start;
                            }   // else
                        }   // else if
                        else if(!Curr->left && Curr->right)
                        { // inner node with 1 right child
                            if(LR)
                            { // right node
                                TreeNode *Temp = Parent->right;
                                Parent->right = Curr->right;
                                delete Temp;
                                return Start;
                            }   // if
                            else
                            {  // left node
                                TreeNode *Temp = Parent->left;
                                Parent->left = Curr->right;
                                delete Temp;
                                return Start;
                            }   // else
                        }   // else if
                        else
                        {  // inner node with 2 children
                            if(LR)
                            { // right node
                                TreeNode *Temp = Parent->right;
                                TreeNode *S = GetSuccessor(Parent->right);  // find Successor
                                Parent->right = S;
                                S->left = Curr->left;
                                delete Temp;
                                return Start;
                            }   // if
                            else
                            {  // left node
                                TreeNode *Temp = Parent->left;
                                TreeNode *S = GetSuccessor(Parent->left);   // find Successor
                                Parent->left = S;
                                S->left = Curr->left;
                                delete Temp;
                                return Start;
                            }   // else
                        }   // else
                    }   // else
                }   // else
            }   // if
            else
            {
                return Start;   // value not found
            }   // else
        }   // Del
    
    public:
        inline TreeNode *deleteNode(TreeNode *root, int key) const noexcept
        {
            return Del(root, root, root, key, 0);
        }   // deleteNode
};  // Solution
