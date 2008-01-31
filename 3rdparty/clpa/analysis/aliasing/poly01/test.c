// Test polymorphic aliasing relationships

// IRQ structures

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

struct irq_desc {
  void (*handle_irq)(unsigned int irq,struct irq_desc *desc,struct pt_regs *regs);
  struct irq_chip         *chip;
  void                    *handler_data;
  void                    *chip_data;
  struct irqaction        *action;
  unsigned int            status;

  unsigned int            depth;
  unsigned int            irq_count;
  unsigned int            irqs_unhandled;
};

struct irq_desc irq_desc[10];

void setup_irq(unsigned int irq, struct irqaction *new)
{
  struct irq_desc *desc = irq_desc + irq;
  struct irqaction *old, **p;

  desc->action = new;
}

void* kmalloc(unsigned);

void request_irq(unsigned int irq,
                 irqreturn_t (*handler)(int, void *, struct pt_regs *),
                 unsigned long irqflags, const char *devname, void *dev_id)
{
  struct irqaction *action = kmalloc(sizeof(struct irqaction));

  action->handler = handler;
  action->flags = irqflags;
  action->name = devname;
  action->next = 0;
  action->dev_id = dev_id;

  setup_irq(irq, action);
}

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

// PCI structures

struct pci_dev {
  void *data;
  int other_stuff[200];
};

struct pci_device_id {};

struct pci_driver {
  char *name;
  void  (*probe)  (struct pci_dev *dev, const struct pci_device_id *id);
};

// IRQ instantiation

struct avmcard {
  char *name;
  int irq;
  int other_stuff[200];
};

struct pci_dev *fake_pci;

irqreturn_t b1_interrupt(int interrupt, void *devptr, struct pt_regs *regs)
{
  struct avmcard *card = devptr;
  struct avmcard *fake_card = fake_pci->data;
  if (fake_card->name == card->name)
    return 0;
  return 1;
}

void b1pci_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
  struct avmcard *card = kmalloc(sizeof(struct avmcard));

  request_irq(card->irq, b1_interrupt, 4, card->name, card);
  pdev->data = card;
}

void fake_b1pci()
{
  fake_pci = kmalloc(sizeof(struct pci_dev));
  b1pci_pci_probe(fake_pci,0);
  handle_IRQ_event(4,0,irq_desc[4].action);
}

static struct pci_driver b1pci_pci_driver = {
  .name           = "b1pci",
  .probe          = b1pci_pci_probe,
};
