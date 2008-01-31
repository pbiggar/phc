typedef unsigned int size_t;

struct mm_share {
 struct { struct mm_share *rbe_left; struct mm_share *rbe_right; struct mm_share *rbe_parent; int rbe_color; } next;
 void *address;
 size_t size;
};

struct mm_master {
 struct mmtree { struct mm_share *rbh_root; } rb_free;
 struct mmtree rb_allocated;
 void *address;
 size_t size;

 struct mm_master *mmalloc;

 int write;
 int read;
};

void mmtree_RB_REMOVE_COLOR(struct mmtree *head, struct mm_share *parent, struct mm_share *elm)
{
  struct mm_share *tmp;
  while ((elm == ((void *)0) || (elm)->next.rbe_color == 0) && elm != (head)->rbh_root) {
    if ((parent)->next.rbe_left == elm) {
      tmp = (parent)->next.rbe_right;
      if ((tmp)->next.rbe_color == 1) {
        do { (tmp)->next.rbe_color = 0;
             (parent)->next.rbe_color = 1; } while (0);
        do { (tmp) = (parent)->next.rbe_right;
             if (((parent)->next.rbe_right = (tmp)->next.rbe_left)) {
               ((tmp)->next.rbe_left)->next.rbe_parent = (parent);
             } ;
             if (((tmp)->next.rbe_parent = (parent)->next.rbe_parent)) {
               if ((parent) == ((parent)->next.rbe_parent)->next.rbe_left)
                 ((parent)->next.rbe_parent)->next.rbe_left = (tmp);
               else ((parent)->next.rbe_parent)->next.rbe_right = (tmp);
             }
             else
               (head)->rbh_root = (tmp);
             (tmp)->next.rbe_left = (parent);
             (parent)->next.rbe_parent = (tmp); ;
             if (((tmp)->next.rbe_parent)) ;
        } while (0);
        tmp = (parent)->next.rbe_right;
      }
      if (((tmp)->next.rbe_left == ((void *)0)
           || ((tmp)->next.rbe_left)->next.rbe_color == 0)
          && ((tmp)->next.rbe_right == ((void *)0)
              || ((tmp)->next.rbe_right)->next.rbe_color == 0)) {
        (tmp)->next.rbe_color = 1; elm = parent;
        parent = (elm)->next.rbe_parent;
      }
      else {
        if ((tmp)->next.rbe_right == ((void *)0)
            || ((tmp)->next.rbe_right)->next.rbe_color == 0) {
          struct mm_share *oleft;
          if ((oleft = (tmp)->next.rbe_left))
            (oleft)->next.rbe_color = 0;
          (tmp)->next.rbe_color = 1;
          do { (oleft) = (tmp)->next.rbe_left;
               if (((tmp)->next.rbe_left = (oleft)->next.rbe_right)) {
                 ((oleft)->next.rbe_right)->next.rbe_parent = (tmp);
               } ;
               if (((oleft)->next.rbe_parent = (tmp)->next.rbe_parent)) {
                 if ((tmp) == ((tmp)->next.rbe_parent)->next.rbe_left)
                   ((tmp)->next.rbe_parent)->next.rbe_left = (oleft);
                 else ((tmp)->next.rbe_parent)->next.rbe_right = (oleft);
               }
               else
                 (head)->rbh_root = (oleft);
               (oleft)->next.rbe_right = (tmp);
               (tmp)->next.rbe_parent = (oleft); ;
               if (((oleft)->next.rbe_parent)) ;
          } while (0);
          tmp = (parent)->next.rbe_right;
        }
        (tmp)->next.rbe_color = (parent)->next.rbe_color;
        (parent)->next.rbe_color = 0;
        if ((tmp)->next.rbe_right)
          ((tmp)->next.rbe_right)->next.rbe_color = 0;
        do { (tmp) = (parent)->next.rbe_right;
             if (((parent)->next.rbe_right = (tmp)->next.rbe_left)) {
               ((tmp)->next.rbe_left)->next.rbe_parent = (parent);
             } ;
             if (((tmp)->next.rbe_parent = (parent)->next.rbe_parent)) {
               if ((parent) == ((parent)->next.rbe_parent)->next.rbe_left)
                 ((parent)->next.rbe_parent)->next.rbe_left = (tmp);
               else
                 ((parent)->next.rbe_parent)->next.rbe_right = (tmp);
             }
             else
               (head)->rbh_root = (tmp);
             (tmp)->next.rbe_left = (parent);
             (parent)->next.rbe_parent = (tmp); ;
             if (((tmp)->next.rbe_parent)) ;
        } while (0);
        elm = (head)->rbh_root;
        break;
      }
    }
    else {
      tmp = (parent)->next.rbe_left;
      if ((tmp)->next.rbe_color == 1) {
        do { (tmp)->next.rbe_color = 0;
             (parent)->next.rbe_color = 1;
        } while (0);
        do { (tmp) = (parent)->next.rbe_left;
             if (((parent)->next.rbe_left = (tmp)->next.rbe_right)) {
               ((tmp)->next.rbe_right)->next.rbe_parent = (parent);
             } ;
             if (((tmp)->next.rbe_parent = (parent)->next.rbe_parent)) {
               if ((parent) == ((parent)->next.rbe_parent)->next.rbe_left)
                 ((parent)->next.rbe_parent)->next.rbe_left = (tmp);
               else
                 ((parent)->next.rbe_parent)->next.rbe_right = (tmp);
             }
             else
               (head)->rbh_root = (tmp); (tmp)->next.rbe_right = (parent);
             (parent)->next.rbe_parent = (tmp); ;
             if (((tmp)->next.rbe_parent)) ;
        } while (0);
        tmp = (parent)->next.rbe_left;
      }
      if (((tmp)->next.rbe_left == ((void *)0)
           || ((tmp)->next.rbe_left)->next.rbe_color == 0)
          && ((tmp)->next.rbe_right == ((void *)0)
              || ((tmp)->next.rbe_right)->next.rbe_color == 0)) {
        (tmp)->next.rbe_color = 1;
        elm = parent;
        parent = (elm)->next.rbe_parent;
      }
      else {
        if ((tmp)->next.rbe_left == ((void *)0)
            || ((tmp)->next.rbe_left)->next.rbe_color == 0) {
          struct mm_share *oright;
          if ((oright = (tmp)->next.rbe_right))
            (oright)->next.rbe_color = 0;
          (tmp)->next.rbe_color = 1;
          do {
            (oright) = (tmp)->next.rbe_right;
            if (((tmp)->next.rbe_right = (oright)->next.rbe_left)) {
              ((oright)->next.rbe_left)->next.rbe_parent = (tmp);
            } ;
            if (((oright)->next.rbe_parent = (tmp)->next.rbe_parent)) {
              if ((tmp) == ((tmp)->next.rbe_parent)->next.rbe_left)
                ((tmp)->next.rbe_parent)->next.rbe_left = (oright);
              else
                ((tmp)->next.rbe_parent)->next.rbe_right = (oright);
            }
            else
              (head)->rbh_root = (oright);
            (oright)->next.rbe_left = (tmp);
            (tmp)->next.rbe_parent = (oright); ;
            if (((oright)->next.rbe_parent)) ;
          } while (0);
          tmp = (parent)->next.rbe_left;
        }
        (tmp)->next.rbe_color = (parent)->next.rbe_color;
        (parent)->next.rbe_color = 0;
        if ((tmp)->next.rbe_left)
          ((tmp)->next.rbe_left)->next.rbe_color = 0;
        do { (tmp) = (parent)->next.rbe_left;
             if (((parent)->next.rbe_left = (tmp)->next.rbe_right)) {
               ((tmp)->next.rbe_right)->next.rbe_parent = (parent);
             } ;
             if (((tmp)->next.rbe_parent = (parent)->next.rbe_parent)) {
               if ((parent) == ((parent)->next.rbe_parent)->next.rbe_left)
                 ((parent)->next.rbe_parent)->next.rbe_left = (tmp);
               else
                 ((parent)->next.rbe_parent)->next.rbe_right = (tmp);
             }
             else
               (head)->rbh_root = (tmp);
             (tmp)->next.rbe_right = (parent);
             (parent)->next.rbe_parent = (tmp); ;
             if (((tmp)->next.rbe_parent)) ;
        } while (0);
        elm = (head)->rbh_root;
        break;
      }
    }
  }
  if (elm)
    (elm)->next.rbe_color = 0;
}
