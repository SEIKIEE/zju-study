static ssize_t new_sync_read_crypt(struct file *filp, char __user *buf, size _t len, loff_t *ppos)
{
int i;
char* mybuf = (char*)kmalloc(sizeof(char)*len,GFP_KERNEL);
ssize_t ret = new_sync_read(filp, buf, len, ppos);
copy_from_user(mybuf, buf, len);
for(i = 0;i < len;i++)
{
mybuf[i] = (mybuf[i] - 25 + 128) % 128;
}
copy_to_user(buf, mybuf, len);
printk("haha encrypt %ld\n", len);
return ret;
}