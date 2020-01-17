static ssize_t new_sync_write_crypt(struct file *filp, const char __user *bu f, size_t len, loff_t *ppos)
{
	char* mybuf = (char*)kmalloc(sizeof(char)*len,GFP_KERNEL);
	int i;
	copy_from_user(mybuf, buf, len);
	for(i = 0;i < len;i++)
	{
		mybuf[i] = (mybuf[i] + 25) % 128;
	}
	copy_to_user(buf, mybuf, len);
	printk("haha encrypt %ld\n", len);
	return new_sync_write(filp, buf, len, ppos);
}