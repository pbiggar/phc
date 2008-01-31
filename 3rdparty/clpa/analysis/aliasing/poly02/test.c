// test identification of possible polymorphic aliasing relationships

typedef unsigned int irqreturn_t;

struct pt_regs {};

struct irqaction {
  irqreturn_t (*handler)(int, void *, struct pt_regs *);
  unsigned long flags;
  const char *name;
  void *dev_id;
  struct irqaction *next;
  int irq;
};

irqreturn_t handle_IRQ_event(unsigned int irq, struct pt_regs *regs,
                             struct irqaction *action)
{
  irqreturn_t ret, retval = 0;

  do {
    ret = action->handler(irq, action->dev_id, regs);
    retval |= ret;
    action = action->next;
  } while (action);

  return retval;
}
