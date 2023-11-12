# About

This repository contains Ansible and Terraform files for quickly deploying a testing environment for Capture The Flag (CTF) challenges and Bug Bounty activities using LXD containers with a BlackArch setup on top of an Arch Linux container.

## Prerequisites

Before getting started, ensure you have the following prerequisites:

- [Ansible](https://www.ansible.com/) installed on your control machine.
- [Terraform](https://www.terraform.io/) installed on your control machine.
- [LXD](https://linuxcontainers.org/lxd/) installed on your host system.
- Ansible collections are installed.
- Python3 is installed in the container.

```bash
ansible-galaxy collection install community.general -f
```

## Usage

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/mohabaks/dotfiles.git
   ```

2. Navigate to the repository directory:

   ```bash
   cd dotfiles/automation
   ```

3. Configure your environment by modifying the Ansible and Terraform files as needed to match your specific requirements.

4. Deploy the environment using Terraform:

   ```bash
   terraform init
   terraform apply
   ```

5. Use Ansible playbooks to configure the containers with the necessary tools and settings:

   ```bash
   ansible-playbook playbooks/setup-blackarch.yml
   ```

6. You now have a fully configured testing environment for your CTF and Bug Bounty activities.

## Customization

Feel free to customize the Ansible and Terraform files to tailor the environment to your specific needs. You can add or remove containers, install additional tools, or adjust network configurations as required.

## Gui Apps

To create a quick script for launching a GUI application like Burp Suite and make it accessible through a `.desktop` file, you can follow these steps:

1. Create a Bash script to launch Burp Suite. For example, create a file named `burpsuite.sh`:

   ```bash
   #!/bin/bash
   APP="burpsuite"
   
   lxc exec blackarch -- sudo --user $USER --login "$APP" $@
   ```

2. Make the script executable:

   ```bash
   chmod +x burpsuite.sh
   ```

3. Create a `.desktop` file to make it accessible in your applications menu. For example, create a file named `burpsuite.desktop` in the `~/.local/share/applications` directory:

   ```ini
   [Desktop Entry]
   Name=Burp Suite
   Comment=Web Application Security Testing
   Exec=/path/to/burpsuite.sh
   Icon=/path/to/burpsuite_community/icon.png
   Terminal=false
   Type=Application
   Categories=Security;Network;
   ```

   - Replace `/path/to/burpsuite.sh` with the full path to your `burpsuite.sh` script.
   - Replace `/path/to/burpsuite_community/icon.png` with the path to the Burp Suite icon, which you can usually find in the Burp Suite installation directory.

4. Save the `.desktop` file.

Now, you should be able to access and launch Burp Suite from your applications menu.

Make sure to customize the paths and icon file to match your specific Burp Suite installation and preferences. Additionally, ensure that the `.desktop` file is placed in the correct directory for your desktop environment to recognize it.
 

## Cleanup

When you're done with your testing environment, you can destroy it using Terraform:

```bash
terraform destroy
```