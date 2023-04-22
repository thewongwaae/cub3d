/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwong <hwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:26:45 by hwong             #+#    #+#             */
/*   Updated: 2023/04/22 16:52:28 by hwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Allocate and initialise first node of flood queue
*/
t_queue	*init_queue( void )
{
	t_queue	*q;

	q = (t_queue *) malloc (sizeof(t_queue));
	q->head = NULL;
	q->tail = NULL;
	return (q);
}

/*
	Check whether queue is empty
*/
int	is_q_empty( t_queue *q )
{
	return (q->head == NULL);
}

/*
	Add new node wwith specified value to the queue
*/
void	enqueue( t_queue *q, t_vec val )
{
	t_queue_node	*new_node;

	new_node = (t_queue_node *) malloc (sizeof(t_queue_node));
	new_node->val = val;
	new_node->next = NULL;
	if (is_q_empty(q))
	{
		q->head = new_node;
		q->tail = new_node;
	}
	else
	{
		q->tail->next = new_node;
		q->tail = new_node;
	}
}

/*
	Free iterative flood queue
*/
t_vec	dequeue( t_queue *q )
{
	t_queue_node	*tmp_node;
	t_vec			val;

	if (is_q_empty(q))
		return ((t_vec){-1, -1});
	tmp_node = q->head;
	val = tmp_node->val;
	q->head = tmp_node->next;
	if (!q->head)
		q->tail = NULL;
	free(tmp_node);
	return (val);
}

/*
	Free iterative flood queue
*/
void	free_queue( t_queue *q )
{
	while (!is_q_empty(q))
		dequeue(q);
	free(q);
}
