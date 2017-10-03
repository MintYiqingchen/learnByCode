#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2017-09-29 22:01:20
# @Author  : mintyi
# @Version : 1.0

#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2017-09-29 22:01:20
# @Author  : mintyi
# @Version : 1.0

import torchvision
import torchvision.transforms as transforms
import torch
transforms = transforms.Compose(
        [transforms.ToTensor(),
        transforms.Normalize((0.5,0.5,0.5),(0.5,0.5,0.5))])
# (RGB_MEAN,RGB_STD)

trainset = torchvision.datasets.CIFAR10(root='./CIFAR', train=True,
                                        download=True, transform=transforms)
trainloader = torch.utils.data.DataLoader(trainset, batch_size=4,
                                          shuffle=True, num_workers=2)

testset = torchvision.datasets.CIFAR10(root='./CIFAR', train=False,
                                       download=True, transform=transforms)
testloader = torch.utils.data.DataLoader(testset, batch_size=4,
                                         shuffle=False, num_workers=2)
classes = ('plane', 'car', 'bird', 'cat',
           'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

import torch.nn as nn
from torch.autograd import Variable
import torch.nn.functional as F

class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(3, 6, 5)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(16*5*5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self,input):
        out = F.relu(self.conv1(input))
        out = self.pool(out)
        out = F.relu(self.conv2(out))
        out = self.pool(out)
        out = out.view(-1, 16*5*5)
        out = F.relu(self.fc1(out))
        out = F.relu(self.fc2(out))
        out = self.fc3(out)
        return out

net = Net()

import torch.optim as optim
optimizer = optim.SGD(net.parameters(),lr=0.001, momentum=0.9)
criterion = nn.CrossEntropyLoss()

for epoch in range(2):
    running_loss = 0.0
    for i, data in enumerate(trainloader):
        inputs, labels = data
        inputs, labels = Variable(inputs), Variable(labels)
        optimizer.zero_grad()

        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
		optimizer.step()

        running_loss += loss.data[0]
        if i%1000 == 999:
            print('[%d, %5d] loss: %.3f' %
                    (epoch+1, i+1, running_loss/1000))
            running_loss = 0.0

print('Finished Training')

# performance evaluation
correct = 0
total = 0
for data in testloader:
    images, labels = data
    outputs = net(Variable(images))
    _, predicted = torch.max(outputs.data, 1)
    total += labels.size(0)
    correct += (predicted == labels).sum()

print('Accuracy of the network on the 10000 test images: %d %%'%(
        100*correct/total))
